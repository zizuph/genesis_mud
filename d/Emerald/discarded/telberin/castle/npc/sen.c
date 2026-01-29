inherit "/std/monster";

#include "/d/Emerald/defs.h"

void
create_monster()
{
    set_name("seneschal");
    add_name("elf");
    set_adj("court");
    set_race_name("elf");
    set_short("court seneschal");
    set_long("This proud elf is the Court Seneschal, the "+
      "chamberlain to their Majesties. He is the one who "+
      "looks after the court and makes sure that everything "+
      "runs smoothly.\n");

    set_base_stat(SS_STR, 100);
    set_base_stat(SS_DEX, 75);
    set_base_stat(SS_CON, 80);
    set_base_stat(SS_INT, 45);
    set_base_stat(SS_WIS, 46);
    set_base_stat(SS_DIS, 80);

    heal_hp(10000);

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 75);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_AWARENESS, 45);

    set_all_hitloc_unarmed(65);  /* Inherent AC of 25 without equip */

    add_prop(OBJ_I_WEIGHT, 14000);
    add_prop(CONT_I_MAX_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);

    set_chat_time(10);                             /* Set speaking interval */
    add_chat("What business do you have with their Majesties?"); /* A bit of 
    random chat */
    add_chat("Can I help you?");
    add_chat("May I present you?");
    add_ask("quest", "The seneschal says: "+VBFC_ME("jewel_chat")+".\n");
    add_ask("jewels", "The seneschal says: "+VBFC_ME("jewel_chat")+".\n");
    add_chat("@@jewel_chat@@");

    set_cchat_time(4);                      /* Set combat speaking interval */
    add_cchat("Guards! Kill these imbeciles!");            /* The usual combat 
    talk */
    add_cchat("Do not shed blood on the court floor!");

    set_act_time(6);                    /* Set action interval           */
    add_act("bow");              /* A few courteous actions       */
    add_act("smile");

}

string
jewel_chat()
{
    if (environment(TO)->query_stolen())
	return "Ack! The queen's jewels have been stolen! The King's men "+
	    "are looking for an Ogre!";
    else
	return "Have you seen the queen's jewels? They're quite impressive, "+
	    "but are locked safely in a vault, so not many people get "+
		"to view them.";
}

public void
add_introduced(string str)
{
    if (this_player()->query_npc())
	return;

    set_alarm(3.0, 0.0, &command("present me to "+lower_case(str)));
    set_alarm(5.0, 0.0, &command("present king to "+lower_case(str)));
    set_alarm(7.0, 0.0, &command("present queen to "+lower_case(str)));
}

public void
announce_guests(object which, string str)
{
    set_alarm(2.0, 0.0, &command("present " + lower_case(str) +
	" to "+ which->query_real_name()));
    set_alarm(4.0, 0.0, &command("present " + which->query_real_name() +
	" to "+ lower_case(str)));
}
