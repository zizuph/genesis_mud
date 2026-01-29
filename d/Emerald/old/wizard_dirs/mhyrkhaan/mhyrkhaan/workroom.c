inherit "/std/workroom";

create_workroom()
{
   set_short("A large marble chamber");
   set_long("The walls in this room are made of huge slabs of black marble. "+
   "There are obsidian pyres lining each side of the room, burning with "+
   "pale, green unatrual flames. There is a desk on the far side of the "+
   "room, with a large chair behind it. As you look around this vast nearly "+
   "empty chamber, you see the ceiling is made entirely of clear crystal. "+
   "Dark foreboding clouds roll by at unnaturally high speeds, spitting torrid "+
   "bolts of lighting which light up the black sky as they roll by. Behind the "+
   "desk, dominating the northern wall, is a huge black, silken banner with a "+
   "large silver symbol of Val-Shoreil in it's center, the silver symbol is "+
   "giving off a soft golw that seems to contrast oddly with the pale green "+
   "light coming from the pyres. The dull roar of the pale flames burning "+
   "in their obsidian pyres, and the great claps of thunder in the sky are the "+
   "only sounds you hear echoing thoughout this huge marble chamber.\n");
   add_item(({"desk","ebony desk"}),"A large desk made of ebony, it "+
   "has papers and maps all over it.\n");
   add_item("banner","A large black banner, the symbol of Val-Shoreil "+
   "glows softly, warming your eyes when you look at it.\n");
   clone_object("/d/Emerald/mhyrkhaan/private/grate")->move(this_object());
   clone_object("/d/Emerald/mhyrkhaan/private/sreen.c")->move(this_object());
   clone_object("/d/Emerald/mhyrkhaan/private/bdoor")->move(this_object());
}
