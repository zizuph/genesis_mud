inherit "std/monster";
inherit "/d/Gondor/common/lib/friend_or_foe";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/tasks.h"
#include "defs.h"

/*
 *  Names of the destinations
 */
#define DEST_NAME ({ "Shire",\
                     "Hobbiton",\
		     "Terel",\
                     "Gondor" })

/*
 *  Filenames of the destinations
 *  /d/Shire/common/mount/path1 is preloaded and clones Gwaihir initially
 */
#define DEST_FILE ({ "/d/Shire/common/guild/rooms/path1",\
                     "/d/Genesis/start/hobbit/v/h_lane1",\
		     "/d/Terel/common/town/road_s/road_s05",\
                     "/d/Gondor/anorien/pelennor/eaglefield" })

/*
 *  Time to stay in a certain destination
 */

#define DEST_WAIT ({ 90.0,\
                     90.0,\
		     90.0,\
		     90.0 })

#define IN_AIR random(90) + 60.0 /* Time of a flight */
#define TAKEOFF_WARNING 30.0 /* He starts to look restlessly before takeoff */

/* Skill-level required to be able to mount */
#define MOUNT_LVL 30

/* Skill-level required to be able to direct */
#define DIRECT_LVL 60

/* The room in which the eagle hides when he is supposed to be flying */
#define TEMP_ROOM STAND_DIR + "gwaihir_sky"

/* Define our own fighting means */
#define ATT_BEAK  0
#define ATT_CLAWS 1

/* Define where we can be hit */
#define HIT_HEAD  0
#define HIT_BODY  1
#define HIT_LWING 2
#define HIT_RWING 3
#define HIT_LPAW  4
#define HIT_RPAW  5

/* Some global variables */
int gFlying, gWhere;

void take_off();

init_living() {
   int i;
   add_action("do_mount","mount");
   add_action("do_leave","leave");
   add_action("do_leave", "dismount");
   for (i=0; i < sizeof(DEST_NAME); i++)
      add_action("do_set_direction",DEST_NAME[i]);
}

choose_exit() {
   /* Choose a new exit */
   while(DEST_FILE[gWhere] == file_name(environment()))
      gWhere = random(sizeof(DEST_FILE));
   tell_room(environment(), "The huge eagle looks restlessly around.\n");
   set_alarm(TAKEOFF_WARNING, 0.0, &take_off());
}

land() {
   move(DEST_FILE[gWhere]);
   tell_room(environment(),
      "A huge eagle descends from the sky and lands here.\n");
   tell_room(this_object(),
      "With high speed the eagle dives to the ground and lands softly.\n");
   gFlying = 0;
   set_alarm(DEST_WAIT[gWhere], 0.0, &choose_exit());
}

void
take_off() {
   tell_room(environment(),
      "The huge eagle stretches his wings and flies off to the sky.\n");
   tell_room(this_object(),
      "You hold on tight as the huge eagle takes off.\n");
   gFlying = 1;
   move(TEMP_ROOM);
   set_alarm(IN_AIR, 0.0, &land());
}

my_long() {
   object tp;
   if (environment(tp = this_player()) == this_object())
   {
      if (gFlying)
         return break_string(
            "You are too afraid you will fall off Gwaihir if you try "
          + "to look down. So, you look up, to find the clouds much "
          + "nearer than they were on the ground. The wind is cold "
          + "and icy up here in the sky. You clench to Gwaihir's "
          + "feathers and hope the journey will be over soon.\n",70);
      else
         return break_string(
            "You cannot make out where you are from the back of "
          + "the huge eagle. One thing is sure; he's standing on "
          + "the ground, so you can leave his back and put your legs "
          + "on the safe floor again.\n",70);
   }
   return break_string(
      "Gwaihir is a huge eagle, big enough to carry a man. He is "
    + "the Windlord of the Eagles. It looks like it is possible to "
    + "mount Gwaihir and travel with him.\n",70);
}

wing_desc() {
   if (gFlying)
      return break_string(
         "The huge wings of Gwaihir have a span of at least 15 ft. "
       + "They seldomly swing, because most of the time Gwaihir floats in "
       + "the air.\n",70);
   else
      return break_string(
         "The wings of Gwaihir are currently folded against his body. You "
       + "can only make a rough estimate of how big they are. They look "
       + "very strong to you.\n",70);
}

do_mount(str) {
   object tp;
   if (gFlying)
      return 0;
   if (!str || str == "")
      return 0;
   str = lower_case(str);
   if(str == "gwaihir" || str == "eagle")
   {
      if (environment(tp = this_player()) != this_object())
      {
         /* Gwaihir does not serve Evil - added by Elessar '94 */
         if (query_friend_or_foe(tp)== -1) {
           write("Gwaihir notices your evil heart.\n"+
             "The Great Eagle easily shrugs you off his back.\n");
             return 1;
             }
         /* Require some animal handling skill */
         if (tp->query_skill(SS_ANI_HANDL) < 30)
         {
            write("You are not good enough at handling animals.\n"
                + "Gwaihir notices it and will not let you mount him.\n");
            return 1;
         }
         else if (tp->query_skill(SS_ANI_HANDL) < 45 && tp->resolve_task(TASK_DIFFICULT, ({ SS_ANI_HANDL })) <= 0)
         {
            write("Your clumsy attempt to mount Gwaihir fails.\n"
               + "Gwaihir shrugs you off his back.\n");
            return 1;
         }
         tp->move(this_object(),1);       /* Move player inside */

         write("You mount Gwaihir by climbing on his back.\n");
         tell_room(environment(),
            QCTNAME(tp) + " mounts the eagle.\n");
         return 1;
      }
   }
}

do_leave(str) {
   object tp;
   if (gFlying)
   {
      notify_fail("As you look at the ground far below you, you quickly"+
         " change your mind.\n");
      return 0;
   }
   if (environment(tp = this_player()) == this_object())
   {
      write("You leave the back of Gwaihir.\n");
      tell_room(environment(),
         QCTNAME(tp) + " climbs off the back of the eagle.\n");
      tp->move(environment());     /* Move to a room, therefore safe */
      return 1;
   }
}

do_set_direction() {
   string str;
   int index, nice_level, listened;

   str = query_verb();
   if (index = member_array(str,DEST_NAME) < 0)
      return 0;

   write("You ask Gwaihir if he will take you to " + capitalize(str) + ".\n");
   say(QCTNAME(this_player()) + " whispers something to the eagle.\n"); 

   /* Use the players animal-handling skill */
   nice_level = this_player()->query_skill(SS_ANI_HANDL);
   if (listened = (nice_level > DIRECT_LVL - 10 + random(20)))
   {
      gWhere = index;
      write("Gwaihir took your advice and will head for the new destination.\n");
   }
   else
      write("You lack enough skill in animal handling to convince Gwaihir.\n");
   return 1;
}

query_gFlying() { return gFlying; }
query_gWhere() { return gWhere; }
query_location() { return file_name(environment()); }
query_destination() { return DEST_FILE[gWhere]; }

create_monster() {
   if (!IS_CLONE)
      return;
   set_name("gwaihir");
   set_title("the Windlord of the Eagles");
   set_race_name("eagle");
   set_adj(({"huge","brown"}));
   set_living_name("gwaihir_eagle");
   set_long("@@my_long");

   add_item(({"wing","wings"}), "@@wing_desc");
   add_item(({ "eagle" }), "From here, you can't make out much more than a"+
      " huge wall of feathers.\n");

   /* Let's turn him into a lean, mean fighting machine :-) */
   set_stats(({ 90, 90, 90, 90, 90 }));
   set_hp(query_max_hp()); /* Heal fully */
   set_skill(SS_UNARM_COMBAT,90);
   set_skill(SS_DEFENCE,90);
   set_pick_up(0);

   set_aggressive(0);
   set_attack_chance(0);

   set_attack_unarmed(ATT_BEAK,  57, 60, W_IMPALE, 30, "beak");
   set_attack_unarmed(ATT_CLAWS, 45, 80, W_IMPALE | W_SLASH, 70, "claws");

   /* Even lean, mean fighting machines can be hit... */
   set_hitloc_unarmed(HIT_HEAD,  ({ 30, 30, 30, 30 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 30, 30, 30, 30 }), 30, "body");
   set_hitloc_unarmed(HIT_LWING, ({ 30, 30, 30, 30 }), 23, "left wing");
   set_hitloc_unarmed(HIT_RWING, ({ 30, 30, 30, 30 }), 23, "right wing");
   set_hitloc_unarmed(HIT_LPAW,  ({ 30, 30, 30, 30 }), 07, "left paw");
   set_hitloc_unarmed(HIT_RPAW,  ({ 30, 30, 30, 30 }), 07, "right paw");

   /* Start on the ground */
   gFlying = 0;
   gWhere = 0;

 /* This bird has been designed to be able to carry at least 20 Fatties :-) */
   add_prop(CONT_I_VOLUME,      100 * 1000);
   add_prop(CONT_I_MAX_VOLUME, 1000 * 1000);
   add_prop(CONT_I_WEIGHT,       89 * 1000);
   add_prop(CONT_I_MAX_WEIGHT, 1000 * 1000);
   add_prop(CONT_I_LIGHT, 1);
   add_prop(LIVE_I_ALWAYSKNOWN,1);

   set_alarm(1.0, 0.0, &choose_exit());
}
