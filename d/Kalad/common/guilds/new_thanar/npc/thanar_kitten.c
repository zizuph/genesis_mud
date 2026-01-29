/*
 * /d/Kalad/common/guilds/new_thanar/npc/ukitten
 *
 * The initial form of the summoned Thanar Deity. A little bit of
 * demonic fun, so to speak.
 */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "../local.h"

inherit "/d/Kalad/std/active_monster_base.c";

#define TYPE ({"plain", "happy", "growling", "friendly", "grim",\
 "lively"})
#define PHYS ({"big-eared", "squinty-eyed", "flat-nosed", "majestic",\
"mangy", "pug-nosed"})
#define EYES ({"blue", "green", "brown", "hazel", "grey"})
#define HAIR ({"grey", "calico", "black", "white", "white-black", \
"striped", "orange"})


int x = 0;
string hishers = "";
string heshe = "";
string himher = "";
string CAPheshe = "";
string CAPhishers = "";

void determine_sex()
{
        switch(random(2))
        {
                case 0:  set_gender(G_MALE);
						 hishers = "his";
						 heshe = "he";
						 himher = "him";
						 CAPheshe = "He";
                         x = 0;
                         break;
                case 1:  set_gender(G_FEMALE);
						 hishers = "her";
						 heshe = "she";
						 himher = "her";
						 CAPheshe = "She";
                         x = 1;
                         break;
                default: set_gender(G_NEUTER);
                         break;
        }
}

nomask void create_active_monster()
{
        determine_sex();
        string type, phys, eyes, hair;
        int i;

        seteuid(getuid());

        type = one_of_list(TYPE);
        phys = one_of_list(PHYS);
        eyes = one_of_list(EYES);
        hair = one_of_list(HAIR);
        

        string npc_name = "undead kittens";

        add_adj(type);
        add_adj(phys);
        add_name("_thanar_kitten_npc");
        add_prop(LIVE_I_NEVERKNOWN, 1);
		add_prop(LIVE_I_SEE_DARK, 1);
		add_prop(LIVE_I_UNDEAD, 1);
		add_prop(CONT_I_WEIGHT, 350);
		add_prop(OBJ_I_WEIGHT, 350);
		add_prop(OBJ_I_VOLUME, 350);
		add_prop(CONT_I_VOLUME, 350);
		add_prop(LIVE_I_NO_GENDER_DESC, 1);

        set_race_name("zombie kitten");
		add_name("kitten");
        switch(hishers)
        {
                case "his":  set_gender(G_MALE);
						 hishers = "his";
						 heshe = "he";
						 himher = "him";
						 CAPheshe = "He";
                         CAPhishers = "His";
                         x = 0;
                         break;
                case "her":  set_gender(G_FEMALE);
						 hishers = "her";
						 heshe = "she";
						 himher = "her";
						 CAPheshe = "She";
                         CAPhishers = "Her";
                         x = 1;
                         break;
                default: break;
        }
		add_name(npc_name);

        set_long("A small "+phys+" "+hair+" undead kitten. On first "
		+"glance this looks like a normal kitten. Sadly its life was ended "
		+"and now it shambles around, its "+eyes+" eyes hanging out of "
		+"one socket. "+CAPheshe+" snarls softly as "+heshe+" scrounges "
		+"looking for flesh to satiate "+hishers+" eternal hunger.\n\n"
        +"As you look at it more closely you realize it is a vessel of some "
        +"sort. Killing it should release the spirit within.\n\n");

              
        for(i = 0; i < 6; i++)
                set_base_stat(i, 80 + random(30));

        set_hitloc_unarmed(1, 10, 15, "head");
        set_hitloc_unarmed(2, 15, 10, "right arm");
        set_hitloc_unarmed(3, 15, 10, "left arm");
        set_hitloc_unarmed(4, 25, 45, "body");
        set_hitloc_unarmed(5, 20, 20, "legs");

        set_skill(SS_UNARM_COMBAT,40);
        set_skill(SS_DEFENCE,70);
        set_skill(SS_AWARENESS,90);

        set_act_time(10);
        add_act("emote meows softly.");
        add_act("emote purrs loudly.");
		add_act("emote cries horrifyingly.");
		add_act("stretch");
		add_act("emote turns in a circle and lays down for a nap.");
		add_act("snore softly");
		add_act("emote nuzzles you.");
		add_act("emote jumps around chasing an invisible bug, "
		+"eye bouncing out of its socket.");


}

void
transform(object enemy)
{
   tell_room(E(TO), "Suddenly the contours of " + QTNAME(TO) + 
             " starts to fade and blur. "+CAPhishers+ " face contorts " +
             "and expands rapidly. "+CAPhishers+" eyes melt inside "+
             hishers+" skull as does all the fur. "+CAPheshe+" rises up "+
             "onto two legs before and all pretence fades immediately away." +
             " Suddenly you realize, that you are facing the Deity " +
             "Thanar!\n", TO);
   seteuid(getuid(TO));
   clone_object(LIV + "thanar")->move(E(TO));
   TO->kill_enemy(enemy);
   remove_object();
}

void
attacked_by(object ob)
{
   object *arr;
   int i;
   ::attacked_by(ob);
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
      arr[i]->notify_ob_attacked_me(TO,ob);
   transform(ob);
}