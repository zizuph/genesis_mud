/* created by Aridor 02/21/94 */

#include "../local.h"

inherit ROOM_BASE

#define MAX_NUM   5

int num = 0;

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("You are standing in a dimly lit cavern. The cavern looks very natural " +
	     "but you still can see some traces of work that has been done here long " +
	     "ago. The ceiling is about two times the height of an average human, and " +
	     "there are a lot of crevices and niches everywhere.\n");
    
    add_exit(CAVERN + "c4","east");
    add_exit(CAVERN + "hall2","south");
    
    DARK;
    
    add_item(({"wall","walls","ceiling","crevice","niche","niches","crevices"}),
	     "Since this is an almost natural cavern, the rocks are jagged, " +
	     "leaving many niches and crevices everywhere. They are too small " +
	     "to be entered, though.\n");
    add_cmd_item(({"crevice","niche","niches","crevices"}),"enter",
		 "They are too narrow to be entered.\n");
}

void
someone_lit_something()
{
    num++;
    if (num > MAX_NUM)
      return;
    if (query_prop(OBJ_I_LIGHT) <= 0)
      return;
    if (!random(4))
      return;
    if (random(4))
      clone_object(LIV + "bat")->move_living("M",TO);
    else
      clone_object(LIV + "gbat")->move_living("M",TO);
    tell_room(TO,"Something starts to move above you.\n");
}

void
reset_thief_room()
{
    num = 0;
}


void
update_internal(int l, int w, int v)
{
    ::update_internal(l,w,v);
    if (l > 0)
      set_alarm(3.0,0.0,"someone_lit_something");
}


