/*
 * Copyright (C) 19-May-1997 by Shadow DeForest.
 *
 * Creator  : Shadowlynx
 * Date     : 19-May-1997
 * Filename : marigold.c
 * Purpose  : A swamp herb which will cure the itching of a
 *            mosquito bite when rubbed onto the affected skin.
 * Credits  : Modified from the original files of
 *              1. </d/Gondor/common/herbs/savory.c>
 *                 by Olorin - April, 1993.
 *              2. </d/Gondor/rohan/plains/l08.c>
 *                 by Gorboth - April, 1996.
 * Includes : Curing effects.
 * Updates  : 29-November-2000
 *              - Updated for implementation into the Genesis domain.
 */

#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Genesis/start/human/defs.h"

void
create_herb()
{
    set_name("flower");
    set_adj(({"bright","yellow"}));
    set_herb_name("marigold");
    set_short("bright yellow flower");
    set_ingest_verb("eat");
    set_unid_long("A bright yellow flower with five petals.\n");
    set_id_long("This bright yellow five-petaled flower is" +
      " known as a marsh marigold, a plant from the family" +
      " Ranunculaceae of the genus Caltha, species of palustris" +
      " which grows in moist meadows and swamps. The marigold is" +
      " famous for its medicinal properties in curing minor" +
      " rashes and insect bites when rubbed on the skin.\n");
    set_herb_value(800);
    set_id_diff(30);
    set_find_diff(5);
    set_effect(HERB_CURING,"mosquito",50);
    set_decay_time(1200);
    set_dryable();
}

public int
rub_herb(string str)
{
    object   poison;
    string   where;

    if (objectp(poison=present("poison",TP)))
    {
	where = poison->query_body_part();

	write("You crush the flower in your hand and rub the fluid" +
	  " from the petals carefully on the skin of your "+where+".\n");
	say(QCTNAME(TP)+" crushes a flower in "+POSSESSIVE(TP)+"" +
	  " hand and rubs the fluid from the petals carefully on" +
	  " the skin of "+POSSESSIVE(TP)+" "+where+".\n");

	poison->cure_poison(({"mosquito"}),50);
    }
    else
    {
	write("You crush the flower in your hand and rub the fluid" +
	  " from the petals on your skin.\n");
	say(QCTNAME(TP)+" crushes a flower in "+POSSESSIVE(TP)+"" +
	  " hand and rubs the fluid from the petals on" +
	  " "+POSSESSIVE(TP)+" skin.\n");
    }
    TO->remove_object();
    return 1;
}

void
init()
{
    ::init();
    add_action(rub_herb,"rub");
}

string   query_recover() { return MASTER+":"+query_herb_recover(); }
void     init_recover(string arg) { init_herb_recover(arg); }
