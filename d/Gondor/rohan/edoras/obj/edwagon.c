/*
 *	/d/Gondor/rohan/edoras/obj/edwagon.c
 *
 *	A wagon to run a transport service from 
 *	Minas Tirith to Edoras.
 *
 *	Originally by Elessar, recoded January 1997 by Olorin.
 *
 *	Modification log:
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/wagon.c";

#include "/d/Gondor/defs.h"

public void
create_wagon()
{
    set_name( ({ "wagon", "carriage", "horse-wagon", 
		 "horse-carriage", "transport", }) );
    set_retour( ({ MINAS_DIR + "e3crc1",
		   MINAS_DIR + "gate1",
		   MINAS_DIR + "ingate1",
		   ANO_DIR + "pelennor/citygate",
		   ANO_DIR + "pelennor/nroad1", 
		   ANO_DIR + "pelennor/nroad2",
		   ANO_DIR + "pelennor/nroad3",
		   ANO_DIR + "pelennor/ningate",
		   ANO_DIR + "pelennor/noutgate",
		   ANO_DIR + "road/wr1",
		   ANO_DIR + "road/wr2",
		   ANO_DIR + "road/wr3",
		   ANO_DIR + "road/wr4",
		   ANO_DIR + "road/wr5",
		   ANO_DIR + "road/wr6",
		   ANO_DIR + "road/wr7",
		   ANO_DIR + "road/wr8",
		   ANO_DIR + "road/wr9",
		   ANO_DIR + "road/wr10",
		   ANO_DIR + "road/wr11",
		   ANO_DIR + "road/wr12",
		   ANO_DIR + "road/wr13",
		   ANO_DIR + "road/wr14",
		   ROH_DIR + "road/mering",
		   ROH_DIR + "road/er7",
		   ROH_DIR + "road/er6",
		   ROH_DIR + "road/er5",
		   ROH_DIR + "road/er4",
		   ROH_DIR + "road/er3",
		   ROH_DIR + "road/er2",
		   ROH_DIR + "road/er1",
		   ROH_DIR + "road/crossroad",
		   ROH_DIR + "road/graves",
		   EDORAS_DIR + "city_entr",
		   EDORAS_DIR + "gate", 
		   EDORAS_DIR + "ingate", 
		   EDORAS_DIR + "path2", 
	       }) );
    set_tour( ({ EDORAS_DIR + "path2", 
		 EDORAS_DIR + "ingate", 
		 EDORAS_DIR + "gate", 
		 EDORAS_DIR + "city_entr",
		 ROH_DIR + "road/graves",
		 ROH_DIR + "road/crossroad",
		 ROH_DIR + "road/er1",
		 ROH_DIR + "road/er2",
		 ROH_DIR + "road/er3",
		 ROH_DIR + "road/er4",
		 ROH_DIR + "road/er5",
		 ROH_DIR + "road/er6",
		 ROH_DIR + "road/er7",
		 ROH_DIR + "road/mering",
		 ANO_DIR + "road/wr14",
		 ANO_DIR + "road/wr13",
		 ANO_DIR + "road/wr12",
		 ANO_DIR + "road/wr11",
		 ANO_DIR + "road/wr10",
		 ANO_DIR + "road/wr9",
		 ANO_DIR + "road/wr8",
		 ANO_DIR + "road/wr7",
		 ANO_DIR + "road/wr6",
		 ANO_DIR + "road/wr5",
		 ANO_DIR + "road/wr4",
		 ANO_DIR + "road/wr3",
		 ANO_DIR + "road/wr2",
		 ANO_DIR + "road/wr1",
		 ANO_DIR + "pelennor/noutgate",
		 ANO_DIR + "pelennor/ningate",
		 ANO_DIR + "pelennor/nroad3",
		 ANO_DIR + "pelennor/nroad2",
		 ANO_DIR + "pelennor/nroad1", 
		 ANO_DIR + "pelennor/citygate",
		 MINAS_DIR + "ingate1",
		 MINAS_DIR + "gate1",
		 MINAS_DIR + "e3crc1",
	     }) );

    set_retour_goal("Edoras");
    set_tour_goal("Minas Tirith");
    set_max_passengers(5);
    set_max_horses(4);

    if (!set_wagon_inside(EDORAS_DIR + "obj/ed_inwagon"))
	log_file("bugs", file_name(TO) + "could not find " +
		 EDORAS_DIR + "obj/ed_inwagon" + ".\n");
}

public string
query_pay_prop()
{
    return "_Gondor_Ed_Wagon";
}

