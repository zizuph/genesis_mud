inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/greenfields/camp/tent.h"

void
create_room()
{
   set_short("Inside an orc tent");
   set_long("This tent is dark, unlike all the rest, and as you walk "+
   "across the floor you notice it is uneven with piles of cloth "+
   "and other things you cannot determine from your feet."+
   " The camp outside seems invitingly pleasant compared to this "+
   "dark, dank, smelly place.\n");
   

   add_item(({"camp","outside"}), "The camp is outside, but you cannot "+
   "see it from in here.\n");
     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,0);
   
     add_exit(GREEN_DIR + "camp/camp05","out",0,1);
}


void
enter_inv(object ob, object from)
{

   object sack, feather;
    ::enter_inv(ob, from);

   if(!interactive(ob)) { return; } /* he's got to be a player to do our quest */
   if(!ob->query_prop("_feather_quest")) { return; } /* Must be doing the quest */

    if (ob->query_prop("_i_got_the_feather")) { return; }

   if(ob->query_skill(SS_AWARENESS) < 20 + random(15)) { return; }
   if(ob->query_skill(SS_LOC_SENSE) < 20 + random(15)) { return; }
   /* Need these skills to detect the feather amid the other chaos */
   if(ob->query_stat(4) < 40 + random(10)) { return; }
   if(ob->query_stat(5) < 40 + random(10)) { return; }
   /* Here we require the player to have some int and wis :) */

    ob->add_prop("_i_got_the_feather",1);

    sack = clone_object(GREEN_DIR + "obj/sack");
    sack->move(ENV(ob));  /* Put the sack in the room */

    feather = clone_object(GREEN_DIR + "obj/feather");
    feather->move(sack,1);   /* Put the feather in the sack */

    return;

}
