
#include "../local.h";

inherit SOLACE_ROOM_BASE;

object mino1, mino2;

void
reset_solace_room()
{
    if (!mino1)
      (mino1 = clone_object(LIV + "minotaur1.c"))->move(TO);
    if (!mino2)
      (mino2 = clone_object(LIV + "minotaur2.c"))->move(TO);
}       

void
create_solace_room() 
{
    set_short("Woods by Crystalmir Lake");
    set_long("You have entered some dark, rather nasty woods to the south " +
	     "of an encampment. It seems that these guards like the " +
	     "darkness, and would rather appreciate it if you would leave " +
	     "them alone to enjoy it. It doesn't look like this is a very " +
	     "likely place to enter the camp.\n");
    add_item(({"woods","trees","forest"}),
	     "These woods are dark. And dirty. And bloody. Ever since the " +
	     "armies of darkness took over, it doesn't seem anything can " +
	     "stay alive in these woods.\n");
    add_exit(ROOM + "camp_ent","northwest",0);
    add_exit(ROOM + "campfire","north","@@check_mino");
    reset_room();
}

int
check_mino()
{
    if ((mino1 || mino2) && (CAN_SEE(mino1, TP) || CAN_SEE(mino2, TP)))
      {
	  write("The minotaur stops you from entering the camp!\n");
	  return 1;
      }
    return 0;
}

