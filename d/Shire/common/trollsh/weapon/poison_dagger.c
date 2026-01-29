/*
 * /d/Gondor/common/wep/poison_dagger.c
 * Based on poison dagger of Gondor.
 * Finwe, January 2003
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

#include "/d/Shire/sys/defs.h"

#define DADJ    ({"dark", "deadly", "black", "jagged", "wicked", })

/*
 *      Prototypes:
 */
static string  long_desc();

/*
 *      Global variables:
 */
static int     Poison_Left = 9;
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
    set_default_weapon(20,19,W_KNIFE,W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,19) + random(100)+288);

    create_poison_dagger();

//    set_long(long_desc);
    set_long("This " + Main_Adj + " " + Extra_Adj +	" dagger is made " +
        "of iron. It's perfectly balanced with a long blade and a simple " +
        "hilt. The blade's edges are sharp and meet at a point. The " +
        "hilt is large enough for one hand. @@query_film@@ film coats the blade.\n");
write(">>\n\n" + Poison_Left + "\n\n");
}

static string
long_desc()
{
    string txt = "This " + Main_Adj + " " + Extra_Adj +	" dagger is made " +
        "of iron. It's perfectly balanced with a long blade and a simple " +
        "hilt. The blade's edges are sharp and meet at a point. The " +
        "hilt is large enough for one hand. @@query_film@@ film coats the blade.\n";
write("\n\n" + Poison_Left + "\n\n");
    return (txt);
}

/*
 * We redefine did_hit() in order to actually poison the player.  We will
 * set it up so that the poison wears off the blade after a while.
 */

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;
    int poison_chance = random(5);

    FIXEUID;
 
    if (phurt <= 1)
        return 0;
    switch(poison_chance)
    {
        case 0: // 20% chance of poisoning enemy.
            if (Poison_Left > 0)
            {
                Poison_Left--;
                if (strlen(Poison_File))
                {
                    if ( (file_size(Poison_File) > 0) ||
                    (file_size(Poison_File + ".c") > 0))
                        poison = clone_object(Poison_File);
                    else
                        log_file("curses", "ERROR: "+file_name(TO) + 
                            " tries to load a non-existing file: " + 
                            Poison_File + "!\n");
                }
                else
                {
                    poison = clone_object("/std/poison_effect");
                    poison->set_time(2000);            /* Nice and long */
                    poison->set_interval(20+random(10));
                    poison->set_strength(50+random(15));
                    poison->set_damage(({POISON_HP, 100, POISON_STAT, SS_STR}));
                }

                poison->move(enemy);
                poison->start_poison();
                log_file("curses",enemy->query_name()+ " poisoned with " + 
                    poison->query_poison_type()+" by " + 
                    query_wielded()->query_name() + ", using a " + short() + 
                    ". " + ctime(time()) + ".\n");
                query_wielded()->catch_msg("You stab your enemy in the " + 
                    hdesc + ", twisting the blade, and leaving behind " +
                    "a trail of poison!\n");
            }
            return 0;
        break;

        case 1..4:
            return 0;
        break;            

    }
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

public int query_doses() 
{ 
    return Poison_Left; 
}

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

string query_film()
{

    switch(Poison_Left)
    {
        case 0: return "transparent"; break;
        case 1: return "A thin"; break;
        case 2: return "A faint"; break;
        case 3: return "A light"; break;
        case 4: return "A glossy"; break;
        case 5: return "A shiny"; break;
        case 6: return "A cloudy"; break;
        case 7: return "A grey"; break;
        case 8: return "A dull"; break;      
        case 9: return "A dark"; break;

    }
}