inherit "/std/workroom";

create_workroom()
{
   set_short("A comforatble bed chamber");
   set_long("This room is a large bed chamber. On the white marble floor there is "+
   "a beutiful red velvet rug, with a black sigil of Kalad in it's center. "+
   "There is an intricate gold pyre, in each corner of the room casting a comfortable, "+
   "soft light on the room. The bed in the center is large and plush. There is a bath here as well.\n");
   clone_object("/d/Kalad/mhyrkhaan/private/bed.c")->move(this_object());
   clone_object("/d/Kalad/mhyrkhaan/private/bath.c")->move(this_object());
   clone_object("/d/Kalad/mhyrkhaan/private/wdoor")->move(this_object());
}
