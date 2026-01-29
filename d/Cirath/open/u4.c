inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
public void
/* by Antharanos */
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_M_NO_TELEPORT,1);
    add_prop(OBJ_S_SEARCH_FUN, "search_floor");
    set_short("Cave");
    set_long("You can barely see within the dark confines of this cave. "+
      "It seems you've reached a dead end, literally. For the only thing "+
      "that lies east is a solid stone wall and just below that are the "+
      "skeletal remains of some creature.\n");
    add_item(({"solid stone wall","solid wall","stone wall","wall"}),
      "It is rough and unworked, clearly a natural cave wall.\n");
    add_item(({"skeletal remains","remains"}),"A few scattered bones of "+
      "some humanoid creature lie about the floor, it looks human but you cannot be sure that it "+
      "is.\n");
    add_item(({"floor"}),"The floor is relatively smooth in comparison "+
      "with the walls and seems to be more level than other sections of the "+
      "cave floor to the west.\n");
    add_exit(CPASS(underdark/u3),"west","@@check_drowwep",0);
}
public string
search_floor(object me, string arg)
{
    if (arg != "floor")
	return "";
    if (TP->query_skill(SS_AWARENESS) < 30)
	return "";
    add_exit(CPASS(underdark/u5),"down");
    set_alarm(12.0,0.0,"remove_exit","down");
    return "You search the floor carefully and discover a hidden exit leading down.\n";
}
check_drowwep()
{
    object *ob;
    int i;
    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->id("drowwep"))
	{
	    write("Your drow weapon disintegrates!\n");
	    ob[i]->remove_object();
	    return 0;
	}
    return 0;
}
