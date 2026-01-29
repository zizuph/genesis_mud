#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;
inherit "/lib/unique"; 

#define KNIGHT_NPC "/d/Krynn/solamn/vin/std/vin_knight_base"

#define STRALLE_WANTS_THIS

object knight1;
object knight2;
object knight3;
object knight4;

void
reset_flotsam_room()
{
    if(!objectp(knight1))
    {
	knight1 = clone_object(KNIGHT_NPC);
#ifdef STRALLE_WANTS_THIS
	knight1->set_level(8 + random(2));
    clone_unique(WEAPON + "flail", 3, "/d/Krynn/solamn/vin/weapon/s_mace")->move(knight1, 1);
	knight1->move(TO);
    knight1->command("unwield all");
    knight1->command("wield flail");
#else
    knight1->move(TO);
#endif
    knight1->refresh_living();
    }
    if(!objectp(knight2))
    {
	knight2 = clone_object(KNIGHT_NPC);
#ifdef STRALLE_WANTS_THIS
    knight2->set_level(5 + random(2));
#endif
	knight2->move(TO);
    knight2->refresh_living();
    }
    if(!objectp(knight3))
    {
	knight3 = clone_object(KNIGHT_NPC);
#ifdef STRALLE_WANTS_THIS
    knight3->set_level(2 + random(3));
#endif
	knight3->move(TO);
    knight3->refresh_living();
    }
    if(!objectp(knight4))
    {
	knight4 = clone_object(KNIGHT_NPC);
	knight4->move(TO);
    knight4->refresh_living();
    }
}

create_flotsam_room()
{
    set_short("Underground hall of a covert Circle of Knights");
    set_long("@@long_descr");

    add_item(({"great underground hall","underground hall","hall"}),
      "@@long_descr");
    add_item(({"earthern walls","walls","wall"}),"The earthern walls " +
      "are smooth and well cut. Torches in sconces are spaced at intervals " +
      "along the walls, with great tapestries between them.\n");
    add_item(({"long table","table"}),"This is a long mahogany table. " +
      "In the centre of the table is a carving of a kingfisher carrying " +
      "a sword that is entwined with a rose. A crown is carved under it. " +
      "This table seems to be used for meetings of a sort.\n");
    add_item(({"kingfisher","crown","rose","sword","carving"}),
      "In the centre of the table is a carving of the traditional symbols " +
      "of the Solamnian Knighthood.\n");
    add_item(({"great tapestries","tapestries","tapestry"}),
      "These great tapestries are of ancient make. They depict Knights " +
      "of Solamnia in glorious battle against many different forces " +
      "of evil.\n");
    add_item(({"sconces","lit torches","torches"}),"Torches in sconces " +
      "are attached to the wall. They cannot be taken.\n");
    add_item(({"rack","weapons rack"}),"This weapons rack contains arms " +
      "for the knights stationed here. " +
      "It is closed, locked and bolted. \n");
    add_item(({"iron ladder","ladder"}),"An iron ladder leads up to the " +
      "farmhouse above.\n");

    add_exit(FROOM + "fireplace","up",0);
    add_exit(FROOM + "hall15","north",0);
    add_exit(FROOM + "hall6","south",0);
    add_exit(FROOM + "new_office","west",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in a great underground hall of a covert Knights Circle under " +
    "the farmhouse. Its earthern walls are illuminated by lit torches " +
    "attached to sconces, which light up great tapestries. A long " +
    "table sits in the middle of the room, and a weapon rack sits " +
    "at the back. There is an iron ladder against the eastern wall " +
    "that leads upwards.\n";
}

