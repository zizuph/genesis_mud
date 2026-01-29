/* 
 * Map vendor from Aesthetics who sells maps of the
 * city for 4gc in the palatial plaza.
 * Mortis 08.2005
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"


inherit CITIZEN;
inherit "/d/Ansalon/common/cheater";

#define MONEY 3000 + random(5000)

void
create_krynn_monster()
{
    set_name("edgus");
    set_race_name("human");
	set_living_name("edgus");
    set_adj("grey-bearded");
    add_adj("maroon-robed");
	add_name(({"mapmaker", "mapman", "mapseller", "mapvendor", "edgus"}));
	set_title("the Map Vendor and Aesthetic en Retirum");
    set_long("Before you is a smiling, old man perhaps in his early sixties "
	+ "with a full, grey beard.  Hanging from his wide, maroon cloth belt "
	+ "are several polished, darkwood scroll cases from which he is selling "
	+ "maps of the city.\n");
    set_stats(({30,30,80,80,90,50}));
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_AWARENESS, 45);
    set_skill(SS_UNARM_COMBAT, 45);
    add_prop(OBJ_M_HAS_MONEY, MONEY);
	set_introduce(1);
    set_act_time(15);
    add_act("say Maps for sale.  Most detailed in the city.");
    add_act("emote adjusts a scroll case at his belt.");
    add_act("emote smiles kindly as a young aesthetic walks up to him and "
	+ "hands him a roll of crisp, new scrolls.");
    add_act("say May I offer you a map?  They are four gold coins.");
    add_act("nods his head and smiles in a kind manner.");
    add_act("time");
	add_act("smell");
	add_act("get maps");
    add_act("emote procures a handkerchief from within his robes with which "
	+ "he dabs at his forehead before replacing it, smiling gently.");

    add_ask(({"map","maps","price","list"}),
      "Edgus replies:  I sell maps of the city of Palanthas from the order "
	+ "of Aesthetics.  They are only four gold coins, and I highly recommend "
	+ "them to new visitors.\n");

	add_ask(({"aesthetic", "aesthetics", "order", "brotherhood"}), "Edgus "
	+ "replies:  The Aesthetics are an order of monks devoted to the study of "
	+ "all spheres of scholarly learning.  The southern quarter of the city "
	+ "is known as the Aesthetics district.  There you can find their "
	+ "monastery, cheap accomodations, and the Great Library of Palanthas "
	+ "where Astinus himself is at this very moment writing the history of "
	+ "the world up to the present!\n");

	add_ask("astinus", "Edgus replies:  Ahh, he is the greatest Aesthetic and "
	+ "gifted with a sight from the gods.  He sees all history as it occurs "
	+ "and scribes it into the great tomes of history.  He rarely accepts "
	+ "visitors, but if you desire an audience, he can be found in his study "
	+ "in the great library.  It is one of many attractions on my maps.\n");

	add_ask("library", "Edgus replies:  The Great Library of Palanthas is "
	+ "just south of here off Inner Circle street.  You'll find a great many "
	+ "books on a wide variety of subjects there.  The Aesthetics run the "
	+ "library quite well.\n");

}

void
init_living()
{
    ::init_living();
    ADA("buy");
}


buy(str)
{
    object pmap;
    NF("Buy what did you say?  I sell only maps.\n");
    if(!str || (str != "map"))
	return 0;

    if (check_cheater(TP, TO))
	return 1;
    NF("I am sorry, but you need four gold to purchase a map.\n");
    if(!MONEY_ADD(TP, -576))
	return 0;

    write("The old mapmaker's eyes crinkle up as he smiles pleasantly.  "
	+ "He opens one of the scroll cases at his belt and slides out a "
	+ "new map.  Unfurling it, he hands it to you and takes his payment.\n");

    say("The old mapmaker's eyes crinkle up merrily as " +QTNAME(TP)
	+ " passes him some money.  The mapmaker opens one of his scroll cases, "
    + "slides out a new map, unfurls it, and hands it to " +QTNAME(TP)+ ".\n");

    pmap = clone_object(OBJ + "pal_map");
    pmap->move(TP);
    return 1;
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "map_robe")->move(TO, 1);
    clone_object(OBJ + "sandals")->move(TO,1);
    command("wear all");
	MONEY_MAKE_PC(1 + random(3))->move(TO);
	MONEY_MAKE_GC(20 + random(28))->move(TO);
}
