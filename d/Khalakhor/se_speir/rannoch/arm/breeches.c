/* File         : /d/Khalakhor/se_speir/rannoch/arm/breeches.c
 * Creator      : Darragh@Genesis
 * Date         : 00-12-21      
 * Purpose      : Object file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

inherit "/std/armour";

private string query_breeches_one();
private string query_breeches_two();
string ADJI = query_breeches_one();
string ADJII = query_breeches_two();

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

void create_armour()
{
    set_short("pair of "+ ADJI + " "+ ADJII + " breeches");
    set_name("breeches");
    set_adj( ADJI );
    add_adj( ADJII );
    set_long("These "+ ADJI + " "+ ADJII + " breeches are rough, warm, "
           + "and made of wool. Endurance rather than comfort were clearly "
           + "their maker's intention.\n");

    set_ac(1);
    add_prop(OBJ_I_VALUE, 180);
    set_at(A_LEGS);
    set_am( ({0,1,-1 }) );
    set_af(this_object());
}

private string
query_breeches_one()
{
    string *adjectives = ({"striped", "plain", "dirty", "new", "wide",});

    return adjectives[random(sizeof(adjectives))];
}

private string
query_breeches_two()
{
    string *adjectives = ({"light brown", "brown", "grey", "dark grey",});

    return adjectives[random(sizeof(adjectives))];
}

string query_recover() { return 0; }
