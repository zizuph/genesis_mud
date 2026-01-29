/*
 * /d/Shire/herald/book.c
 *
 * The prayer book/spell object for the Heralds of the Valar
 *
 */

#pragma save_binary

inherit "/std/spells";
#include "herald.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"
#include "herald_spells.h"
#include "/d/Shire/bits.h"
#include "khil.h"
#include "silme.h"
#include "ramar.h"
#include "lissinen.h"
#include "vanahwesta.h"
#include "mel.h"
#include "haetir.h"
#include "ondo.h"
#include "engwagalad.h"
#include "palandir.h"
#include "lammen.h"

int craft, is_wiz;

public void
create_spells()
{

    set_name("book");
    add_name(({"_herald_book_", "prayer book"}));
    set_pname("books");  // Should never happen!
    add_adj(({"leather","prayer"}));
    set_short("leather prayer book");
    set_pshort("leather prayer books");  // Should never happen!
    set_long("This is a leather prayer book, richly embossed with "+
      "fourteen powerful figures, one of which is wearing a crown.\n");


    /*
     *  Not all spells will be available at all times. The average of
     *  2*INT+WIS is taken, and that must be above a certain level.
     *  Note that this way of adding the spells has nothing to do with
     *  how successfull someone will be when casting the spell .
     *  Note also that this has nothing to do with how high your rank
     *  is. That only determines how high one can
     *  train her skills.
     *  Of course wizards can always cast everything.
     */
    is_wiz = TP->query_wiz_level();
    craft = (2*(TP->query_stat(SS_INT)) + TP->query_stat(SS_WIS)) / 3;

    if (is_wiz || IS_MEMBER(TP))
    {
	/* Add all spells */
	if (is_wiz || craft >= SP_ADORE_MIN)
	    add_spell("mel", "do_adore_spell", "praise Lorien");
	if (is_wiz || craft >= SP_PALANDIR_MIN)
	    add_spell("palandir", "do_palandir_spell", "to see far away");
	if (is_wiz || craft >= SP_RAMAR_MIN)
	    add_spell("ramar", "do_ramar_spell", "summon messenger");
	if (is_wiz || craft >= SP_SILME_MIN)
	    add_spell("silme", "do_silme_spell", "obtain light");
	if (is_wiz || craft >= SP_ALIGN_MIN)
	    add_spell("khil", "do_align_spell", "discover the enemy");
	if (is_wiz || craft >= SP_LAMMEN_MIN)
	    add_spell("lammen", "do_lammen_spell", "speak in the tongue of Aman");
	if (is_wiz || craft >= SP_PEACE_MIN)
	    add_spell("vanahwesta", "do_peace_spell", "decrease anger");
	if (is_wiz || craft >= SP_TEND_MIN)
	    add_spell("lissinen", "do_tend_spell", "sweet-water healing");
	if (is_wiz || craft >= SP_CURE_MIN)
	    add_spell("engwagalad", "do_cure_spell", "eradicate sickness");
	if (is_wiz || craft >= SP_CLV_MIN)
	    add_spell("haetir", "do_clv_spell", "to watch over from afar"); 
	if (is_wiz || craft >= SP_PROT_MIN)
	    add_spell("ondo", "do_protect_spell", "skin of stone");
    }


    add_prop(OBJ_I_WEIGHT,     1200);          /* 1.2 kg        */
    add_prop(OBJ_I_VOLUME,     500);           /* Empty volume. */
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_VALUE,	0);
    add_prop(OBJ_I_NO_DROP,1);
}


varargs void
enter_env(object dest, object old)
{
    ::enter_env(dest,old);
    if (!living(dest))
	return;

    remove_name("_herald_book_");
    if (present("_herald_book_", ENV(TO)))
    {
	set_alarm(0.1,0.0, remove_object);
	return;
    }
    add_name("_herald_book_");
    if (dest->query_wiz_level() || IS_MEMBER(dest))
	return;

    set_alarm(0.1,0.0,remove_object);
}

void
init()
{
    ::init();
    add_action("do_read","read");
}


int
do_read(string str)
{
    if((str != "prayer book") && (str != "leather book"))
    {
	notify_fail("Read what? The prayer book?\n");
	return 0;
    }

    write("Your prayer book describes which ingredients are necessary "+
      "for each of your spells.\n\n");
    write("The prayer vanahwesta, to Orome, requires a brown mushroom.\n"+
      "The lissinen prayer, to Lorien, requires a huckleberry.\n"+
      "The prayer for engwagald, to Este, needs the herb athelas in order to "+
      "be effective, using the herb pawnrose in conjuction will boost "+
      "the prayers effectiveness.\n"+
      "The haetir prayer is granted through Manwe and a parsley leaf.\n"+
      "The ondo spell of Aule needs a rock, his element, for success.\n"+
      "The prayers mel, silme, ramar, palandir, lammen and khil "+
      "need no ingredients.\n");
    return 1;

}


public string
query_recover() { return 0; }

public int
query_spell_time(string verb)
{
    return 2;
}
