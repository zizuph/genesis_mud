/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP              this_player()
#define TO              this_object()
#define ETP             environment(TP)
#define ETO             environment(TO)
#define DELAY           200
#define EVIL_LIM        -100
#define VERY_EVIL_LIM   -500

public void recharge();

int activated = 1, aid = 0;

public void
init()
{
    ::init();
    if (TP == ETO) {
        add_action("display", "display");
        add_action("invoke", "invoke");
        add_action("hold", "hold");
    }
}

public int
allowed(object ob)
{
    if (!living(ob)) return 1;
    if (T_WIZ(ob)) return 1;
    if (MEMBER(ob) && ob->query_mystic_rank() >= MYSTIC_ARCHON) return 1;
    return 0;
}

public string
query_auto_load()
{
    mixed *calls;
    int time=0;

    if (!allowed(TP)) return "";
    
    if (aid) {
        calls = get_alarm(aid);
        time = ftoi(calls[2]);
    }
    return MASTER + ":" + activated + "##" + time;
}

public void
init_arg(string str)
{
    int time;

    if (sscanf(str, "%d##%d", activated, time) != 2) {
        activated = 1;
    }
    if (!activated) {
        if (time < 1) time = 1;
        aid = set_alarm(itof(time), -1.0, recharge);
    }
}

public void
recharge()
{
    if (ETO && living(ETO))
        ETO->catch_msg("The ivory stars on the " + short() +
                       " shine for a short while.\n");
    activated = 1;
    aid = 0;
}

public void
create_object()
{
   set_name("icon");
   set_adj("holy");
   add_name(MYSTIC_ICON);
   add_name("holy_icon");
   set_long(
      "A mystical icon, an arcane disk of silver. Inlaid upon the disk is "
     +"a diamond shape of bright gold. About the diamond are set four ivory "
     +"stars, one to each side. In the center of the diamond is a small "
     +"graven image of some mysterious power.\n");

   add_item(({"image"}), "It is unfathomable and thus you retain no cogent "
     +"understanding of its shape or design. Only a fleeting "
     +"sensation of its power.\n");

   add_prop(MAGIC_AM_MAGIC, ({50, "conjuration"}));
   add_prop(OBJ_M_NO_SELL, 1);
}

public int
invoke(string str)
{
    object who;

    if (!allowed(TP)) return 0;
    
    notify_fail("Invoke what?\n");
    if (!str) return 0;

    if (!activated) {
        write("The ivory stars on the "+short()+" become even darker.\n");
        return 1;
    }
    if (TP->query_alignment() < HOLY_LIM - 100) {
        write("Seek holiness if you wish to gain " +
              "the powers of the icon.\n");
        return 1;
    }

    notify_fail("Invoke the icon upon who?\n");
    if (!parse_command(str, ETP, "[the] 'icon' [upon] %o", who)) return 0;

    if (who == TP) return 0;

    notify_fail("The invocation fails to find a living target.\n");
    if (!living(who)) return 0;
    if (who->query_ghost()) return 0;

    write("You invoke the holy icon.\n");
    say(QCTNAME(TP) + " reveals a holy icon.\n", ({TP, who}));
    who->catch_msg(QCTNAME(TP) + " traces the holy icon before you.\n");

    if (who->query_alignment() < VERY_EVIL_LIM) {
        who->catch_msg("A great turbulance strikes your soul!\n");
        tell_room(ETP, QCTNAME(who) + " looks horrified.\n", who);
        TP->attack_object(who);
        who->hit_me(20 + random(10), MAGIC_DT, TP, -1);
    }
    activated = 0;
    aid = set_alarm(itof(DELAY), -1.0, recharge);
    return 1;
}

public int
other_members(object ob)
{
    if (MEMBER(ob) && present(MYSTIC_RING, ob) && ob != TP)
        return 1;
    return 0;
}

public int
hold(string str)
{
    object *mm;
    int i;


    notify_fail("Hold what?\n");
    if (!str) return 0;
    if (str != "icon" && str != "holy icon") return 0;

    write("You hold the sacred icon close to your chest.\n");
    say(QCTNAME(TP) + " holds a sacred icon close to " +
        TP->query_possessive() + " chest.\n");

    mm = filter(users(), other_members);

    if (!sizeof(mm)) {
        TP->catch_msg("You do not sense the presence of " +
                      "other mystics.\n");
        return 1;
    }
    TP->catch_msg("You sense the presence of:\n");
    for (i=0; i<sizeof(mm); i++)
         TP->catch_msg(capitalize(mm[i]->query_real_name()) + " " +
                   mm[i]->query_title() + "\n");

    return 1;
}

public int
display(string str)
{
   int    i;
   object *rl;

   if (!allowed(TP)) return 0;

   notify_fail("Display what?\n");
   if (!str) return 0;
   if (str != "icon" && str != "holy icon") return 0;
   if (!activated) {
      write("The ivory stars on the "+short()+" become even darker.\n");
      return 1;
   }
   if (TP->query_alignment() < HOLY_LIM - 100) {
      write("Seek holiness if ye wish to gain the power of the icon.\n");
      return 1;
   }
   write("You hold aloft the holy icon.\n");
   say(QCTNAME(TP) + " raises aloft a holy icon.\n");
   rl = all_inventory(ETP);
   for (i=0; i<sizeof(rl); i++) {
      if (!living(rl[i])) continue;
      if (rl[i]->query_alignment() < EVIL_LIM) {
         rl[i]->heal_hp(-5) ;
         rl[i]->add_panic(50);
         rl[i]->catch_msg("The icon fills you with dread!\n"
               + "A fiery sensation burns all about you!\n");
      } else {
         rl[i]->catch_msg("A power seems to emanate forth from "
               + "the midst of the icon, you feel a tremour within your"
               + " very being.\n");
      }
   }
   activated = 0;
   aid = set_alarm(itof(DELAY), -1.0, recharge);
   return 1;
}
