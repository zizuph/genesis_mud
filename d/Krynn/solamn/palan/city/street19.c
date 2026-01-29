/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

string
query_to_jail()
{
  return "north";
}

void
create_palan_room()
{

    set_short("Shoikan Grove");
    set_long(BS("You feel extremely unwell here. A dark shadow looms "
         +   "over the trees lining this street. Should it actually "
         +   "be possible that the blackened tower you can make out "
         +   "to the southwest can give you such a terrifying feeling? "
             , SL));

    add_item("trees",BS("You have never seen any trees like these before. "
         +   "They seem to be really alive and watching you.", SL));
    add_item(({"shadow","tower"}),BS("You cannot see very much of the tower through "
         +   "the trees, but you can feel its presence settling heavily "
         +   "over you. Shivers run down your back looking in that "
         +   "direction.", SL));

    add_exit(ROOM + "street20","north",0,1);
    add_exit(ROOM + "tower1","southwest","@@no_one_allowed",10);

}


no_one_allowed()
{
    write(BS("You slowly drudge towards the base of the tower, but the "
       +  "urge to turn and flee comes over you as soon as you are "
       +  "only about halfway down the grove. You get the distinct "
       +  "feeling you won't have a chance to get any closer unless "
       +  "you somehow are invited to.", SL));
    return 1;
}
