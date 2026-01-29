/* File         : /d/Khalakhor/se_speir/rannoch/arm/skirt.c
 * Creator      : Darragh@Genesis
 * Date         : 00-12-21      
 * Purpose      : Object file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

inherit "/std/armour";

private string query_skirt_one();
private string query_skirt_two();
string ADJI = query_skirt_one();
string ADJII = query_skirt_two();

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

void create_armour()
{
    set_short(""+ ADJI + " "+ ADJII + " skirt");
    set_name("skirt");
    set_adj( ADJI );
    add_adj( ADJII );
    set_long("This is a "+ ADJI + " "+ ADJII + " skirt, worn by women "
           + "and made of linen. It is wide enough to let the wearer "
           + "move freely.\n");

    set_ac(1);
    add_prop(OBJ_I_VALUE, 150);
    set_at(A_LEGS);
    set_am( ({0,1,-1 }) );
    set_af(this_object());
}

private string
query_skirt_one()
{
    string *adjectives = ({"long", "wide", "dirty", "torn",});

    return adjectives[random(sizeof(adjectives))];
}

private string
query_skirt_two()
{
    string *adjectives = ({"white", "brown", "grey", "dark grey",
                           "light brown", "dark brown",});

    return adjectives[random(sizeof(adjectives))];
}

string query_recover() { return 0; }
