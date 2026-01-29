/*
 * /d/Gondor/common/wep/poison_dagger.c
 *
 * A poisoned dagger
 *
 * Configurations saves now, Fysix, Feb 1997
 * create_weapon declared nomask, 
 * call to create_poison_weapon() added, Olorin, 05-aug-1997
 * Fix bug in recovery -- must recover both adj's. Gnadnar 08-Oct-1998
 * 
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define DADJ    ({"sharp", "shiny", "black", "silver", "jagged", "wicked", })

/*
 *      Prototypes:
 */
static string  long_desc();

/*
 *      Global variables:
 */
static int     Poison_Left = 1;
static string  Extra_Adj, Main_Adj = "long",
               Poison_File;

nomask void
configure_dagger(string extra_adj, string main_adj = "long")
{
    set_name("dagger");
    set_pname("daggers");
    Main_Adj = main_adj;
    Extra_Adj = extra_adj;
    set_adj( ({ main_adj, extra_adj, "poison", "steel" }) );
    set_short(main_adj + " " + extra_adj + " dagger");
    // Must be added due to the long desc:
}

public void
create_poison_dagger()
{
    configure_dagger(ONE_OF_LIST(DADJ));
}

nomask void
create_weapon()
{
    set_default_weapon(14,15,W_KNIFE,W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14,15) + random(100)+288);

    create_poison_dagger();

    set_long(long_desc);
}

static string
long_desc()
{
    string txt = "This " + Main_Adj + " " + Extra_Adj +
	" dagger is made of steel, with keen edges and a hilt shaped "+
	"to give a better grip. Along the edges you notice a strange runnel.";
    if (Poison_Left)
        txt += " You perceive a sheen of liquid in the runnels.";
    return BSN(txt);
}

/*
 * We redefine did_hit() in order to actually poison the player.  We will
 * set it up so that the poison wears off the blade after a while.
 */

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int
phit)
{
    object poison;

    FIX_EUID;
 
    if (phurt <= 1)
        return 0;
    if (Poison_Left > 0)
    {
        Poison_Left--;
        if (strlen(Poison_File))
        {
            if ( (file_size(Poison_File) > 0) ||
                (file_size(Poison_File + ".c") > 0))
                poison = clone_object(Poison_File);
            else
                log_file("curses", "ERROR: "+file_name(TO)
                    + " tries to load a non-existing file: "
                    + Poison_File + "!\n");
        }
        else
        {
            poison = clone_object("/std/poison_effect");
            poison->set_time(2000);            /* Nice and long */
            poison->set_interval(24);
            poison->set_strength(55);
            poison->set_damage(({POISON_HP, 100, POISON_STAT, SS_STR}));
        }
        poison->move(enemy);
        poison->start_poison();
        log_file("curses",enemy->query_name()+ " poisoned with "
            + poison->query_poison_type()+" by "+query_wielded()->query_name()
            + ", using a "+short()+". "+ctime(time())+".\n");
        query_wielded()->catch_msg(
            "You stab your opponent in the "+hdesc
                + ", and make sure the poison enters the wound!\n");
     }
     return 0;
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "#p_u#"
                        + Poison_Left + "#"+ Poison_File + "#"
                        + Main_Adj + "#" + Extra_Adj + "#";
}

public void
init_recover(string arg)
{
    string dummy,
           main_adj, extra_adj;

    init_wep_recover(arg);
    sscanf(arg, "%s#p_u#%d#%s#%s#%s#%s", 
        dummy, Poison_Left, Poison_File, main_adj, extra_adj, dummy);
    configure_dagger(extra_adj, main_adj);

    // ("0" != 0), so check for this!
    if (Poison_File == "0")
        Poison_File = 0;
}

public void
set_doses(int i)
{
    Poison_Left = i;
}

public int query_doses() { return Poison_Left; }

public void
set_poison_file(string str)
{
    Poison_File = str;
    if (Poison_Left < 1)
        Poison_Left = 1;
}

public string
query_poison_file()
{
    if (!Poison_File)
        return "/std/poison_effect";
    else
        return Poison_File;
}
