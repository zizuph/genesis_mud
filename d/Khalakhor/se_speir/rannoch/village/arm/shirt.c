/* File         : /d/Khalakhor/se_speir/rannoch/arm/shirt.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-13      
 * Purpose      : Object file of the Loch Rannoch area.
 * Related Files: 
 * Comments     : Based on Damaris' random gown
 * Modifications: 
 */

inherit "/std/armour";

private string query_shirt_one();
private string query_shirt_two();
string ADJI = query_shirt_one();
string ADJII = query_shirt_two();

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

void create_armour()
{
    set_short(""+ ADJI + " "+ ADJII + " shirt");
    set_name("shirt");
    set_adj( ADJI );
    add_adj( ADJII );
    set_long("This is a "+ ADJI + " "+ ADJII + " shirt, a practical piece "+
             "of clothing for the people who have neither need nor " +
             "money for more elaborate clothes.\n");

    set_ac(0);
    add_prop(OBJ_I_VALUE, 150);
    set_at(A_BODY);
    set_am( ({0,1,-1 }) );
    set_af(this_object());
}

private string
query_shirt_one()
{
    string *adjectives = ({"warm", "simple", "long", "dirty", "large",});

    return adjectives[random(sizeof(adjectives))];
}

private string
query_shirt_two()
{
    string *adjectives = ({"white", "brown", "grey", "dark green",});

    return adjectives[random(sizeof(adjectives))];
}

string query_recover() { return 0; }
