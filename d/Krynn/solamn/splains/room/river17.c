/* Tree and quest code added by Grace 6/05/96 */
/* created by Aridor 06/21/93 */
/** Navarre Sep 23rd 2009: Fixed alarm issues and wrong commands, as reported by Oltakum. */

#include "../local.h"

inherit OUTSIDE_BASE;

#define QDRAC_XP    3500

int do_quest(object dest);
int quest_check();
void remove_me(object qdrac);

void
create_splains_room()
{
    set_short("On the plains, near a tree");
    set_long("There is a river blocking your path west. The river " +
	     "meanders lazily through the plains, flowing from the north" +
	     "west and continuing south. You are still on the plains, and the " +
	     "grass is just as dry here as everywhere else, since the " +
	     "level of the river is just too low. Beyond the river the "+
           "plains continue, but you can't get across the river. "+
           "A stunted and twisted tree grows nearby, "+
           "its branches so bare they cast no shade.\n");

    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think " +
	     "the ground might just be a little damper here near the river.\n");
    add_item(({"river"}),
	     "It's not a very wide river, and the waterlevel is much lower than the " +
	     "plains. The river is west of you and flows from " +
	     "the north to the south.\n");
    add_item(({"side","other side","beyond","beyond river","beyond the river"}),
	     "The plains across the river look exactly like these, so why would " +
	     "you want to go there?\n");
    add_cmd_item("river",({"swim","enter"}),
	     "The plains across the river look exactly like these, so why would " +
	     "you want to go there?\n");
    add_item("tree", "A small tree so gnarled that it looks like the hands "+
           "of an ancient basket-weaver, arthritic and worn to the bone. "+
           "There are needle-like leaves growing intermittently along the "+
           "branches.\n");
    add_item(({"branches", "branch"}),
           "The branches are very slender and twisted, and look as though "+
           "heavily burdened by the weight of the few scattered needle-like "+
           "leaves which grow from them.\n");
    add_item(({ "needle", "needles", "leaf", "leaves", "needle-like leaves"}),
           "These leaves are green and pointed. They resemble short needles. "+
           "They are the only bit of green visible for miles.\n");

    set_noshow_obvious(1);

    add_exit(ROOM + "river16","south","@@quest_check",3);
    add_exit(ROOM + "plain34","east","@@quest_check",3);
    add_exit(ROOM + "plain28","north","@@quest_check",3);
    
    set_auto_reset(TABLE);
}

void
enter_inv(object dest, object old)
{
    ::enter_inv(dest, old);
    
    if (dest->query_prop("_escape_draconian"))
    {
      set_alarm(2.0, 0.0, &do_quest(dest));
    }
    return;
}

int
quest_check()
{
    object qdrac;

    if ( (qdrac=present("_qdrac2_", TO)) )
    {
         qdrac->command("emote stops you.");
         qdrac->command("say This is the place!");
         return 1;
    }
    
    return 0;        
}

int
do_quest(object dest)
{
    object qdrac;
    string who;

    if ( (dest->query_prop("_escape_draconian")) && (qdrac=present("_qdrac2_", TO)) )
    {
        if (!dest->test_bit("Krynn", 3, 5))
        {
             if ( (dest->test_bit("Krynn",1,0)) || (TP->test_bit("Krynn", 1,2)) )
             {
                qdrac->command("cackle");
                qdrac->command("say Some Solamnian -you- are!");
                qdrac->command("say We wouldn't even have someone like you "+
                       "in our DragonArmies.");
                dest->change_prestige(-4); /* take away prestige */
             }
             seteuid(getuid(this_object()));
             dest->adjust_alignment(-500);
             dest->add_exp_quest(QDRAC_XP);
             dest->set_bit(3, 5);
             dest->remove_prop("_escape_draconian");
             K_QUEST_LOG("quest", "Escape Draconian Quest", TP, QDRAC_XP);
             qdrac->command("say Thank you for your assistance in my escape.");
             qdrac->command("say Here is your reward.");
             write("You feel more experienced!\n");
             qdrac->command("wave");
             set_alarm(2.0, 0.0, &remove_me(qdrac));
             return 1;
         } /* reward player for quest */
         qdrac->command("say Thank you again for your help.");
         qdrac->command("say Unfortunately, I cannot reward you twice for "+
			"your assistance.");       
         TP->remove_prop("_escape_draconian"); 
         qdrac->command("wave");
         set_alarm(2.0, 0.0, &remove_me(qdrac));
         return 1; 
    } /* player did quest already */
  return 0;
} /* player doesn't have the props */

void
remove_me(object qdrac)
{
      say("The draconian prisoner leaves in the direction of the river.\n");
      qdrac->remove_object();       

}
