// Ledge path 4 (/d/Avenir/common/ledge/ledge4.c)
// creator(s): Ilyian
// last update:  June 1995 Kazz - added a light source piece to reset_room
//               Jan  1996 Cirion - added a function to chisel
//                           some pieces of the source from the wall
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/ledge/std_ledge";
inherit "/lib/unique";

#include "ledge.h"

int pieces = 2;

void source_complain();

/* This is a bit convoluted but limits the amount of sources */
public void
reset_room()
{
    object ob = clone_unique(L_SOURCE, 30);
    if (objectp(ob)) {
        ob->remove_object();
        pieces++;
        if (pieces > 10)
            pieces = 10;
    }
}

void
create_room()
{
     AE(LEDGE+"ledge3", "north", 0, 6);
     AE(LEDGE+"ledge5", "south", 0, 0);

     SHORT("On the steep path");
     make_the_room("  The path continues up to the north and down to "
      +"the south. The rock wall to the west contains a long vein "
      +"of glowing rocks that winds up to the top of the cliff "
      +"face. It bathes everything in an eerie light.\n");

    AI(({"ledge","cliff","dropoff","view"}),"Merely looking "
      +"over the dropoff gives "
      +"you a terrifying sense of vertigo. The cliff falls hundreds "
      +"of meters down to a great sea in which appear to be islands. "
      +"The entire great cavern is lit by strange phosphorescent veins "
      +"that run through the ceiling. A narrow path has been carved "
      +"out along the cliff, winding steeply downwards to "
      +"the southern part of the cavern.\n");
    AI(({"sea","ocean"}),"The great underground sea stretches out "
      +"thousands "
      +"of meters beneath you, making for a breathtaking sight. "
      +"Throughout the sea are islands of various sizes, and you can "
      +"even make out a ship or two travelling across the waters. The "
      +"light from above does not penetrate the sea, making it a heavy "
      +"shade of black.\n");
    AI(({"island","islands"}),"There are a number of islands of various "
      +"shapes and sizes far beneath you in the sea. From this height "
      +"you can make out few details, but one larger island in the "
      +"centre seems to contain a city, while others appear to be "
      +"green with forests and vegetation.\n");
    AI(({"ceiling","rocks","cave","cavern","Sybarus"}),
       "Spreading out to "
      +"the east you can see the enormous cavern "
      +"ceiling that stretches over all of the land. It seems to be "
      +"criss-crossed by veins of some substance that sheds a dazzling "
      +"white light. The veins seem more prominent on the eastern "
      +"reaches of the ceiling, many leagues away.\n");
     AI(({"vein", "wall", "rock"}), "@@piece_desc");

     reset_room();
} 

init()
{
  ::init();
  add_action("do_chisel", "chisel", 1);
  add_action("do_chisel", "mine", 1);
  add_action("do_chisel", "break", 1);
  add_action("do_chisel", "chip", 1);
}

string piece_desc()
{
  string str;
  switch(pieces)
    {
      case 0:
        str = "The vein seems to have many scars where "
             +"bits have been broken or chiseled off.\n";
        break;
      case 1 .. 2:
        str = "The vein has many scars where pieces have "
             +"been broken off, but it looks like there "
             +"may be a couple left.\n";
        break;
      case 3 .. 8:
        str = "The vein has a few scratches on it where "
             +"pieces have been broken off, but otherwise "
             +"it is whole.\n";
        break;
      default:
        str = "The vein is whole, with only a couple of "
             +"scratches where pieces have been broken "
             +"off.\n";
        break;
     }

   return "This "
      +"strange type of rock inexplicably "
      +"produces dazzling pulses of unearthly light. This "
      +"particular vein is very thin and small compared to the "
      +"larger ones that run across the cavern ceiling, but it "
      +"is still very bright.\n" + str;
}

int do_chisel(string str) {
  object obj;
  object piece;
  string foo;
  object *inv;

  NFN( CAP(QVB) + " what?");
  if (!str || !strlen(str))
    return 0;

  inv = all_inventory(TP);

  if (!parse_command( str, inv, "[glowing] 'vein' %s", foo))
    return 0;

  notify_fail( CAP(QVB) +" the vein with what?\n");

  if (!parse_command(str, inv, "[glowing] 'vein' 'with' %o", obj))
    return 0;

  if (!obj->query_wielded()) {
    TP->catch_msg( "You aren't wielding the " + obj->short() +".\n");
    return 1;
  }

  if(obj->weapon_type() == "club" ||
     obj->weapon_type() == "bow"  ||
     obj->weapon_type() == "item") {
    TP->catch_msg( "The " + obj->short() +" is not sharp "+
              "enough to chisel anything with.\n");
    return 1;
  }

  if (!pieces) {
      TP->catch_msg( "The vein of glowing rock is exhausted.\n");
      return 1;
  }

  TP->catch_msg( "You chisel at the glowing vein with your " +
                obj->short() +".\n");
  say( QCTNAME(TP) + " hits the glowing vein with "
                +POSSESS(TP)+" "+ obj->short() +".\n" );
  TP->add_fatigue(-15);
  if(random(2))
       obj->set_dull(obj->query_dull() + 1);

  pieces--;
  piece = clone_object(L_SOURCE);
  piece->set_volume(random(14) + 1);
  tell_room(TO, "A "+piece->short()+" breaks off from the "
         +"vein and falls to the ground.\n");
  piece->move( TO, 1 );
  set_alarm(2.0, 0.0, &source_complain());
  WRITE_THIS_LOG(CHISEL_LOG,"chiseled a piece of the source.\n");

  return 1;
}

void source_complain()
{
  FLUX("The light from above suddenly pulses angrily.\n");
}
