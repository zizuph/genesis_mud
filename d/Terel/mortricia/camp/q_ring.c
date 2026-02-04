/* A quest ring. Mortricia 920922 */
// Lilith, Oct 2021: fixed issue where the ring was recovering with
//         short of "iron ring" but the long desc says its gold.
//         it isn't elegant but I don't want to go messing with the
//         quest apparratus that changes it from iron to "gold".

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define CAMP_DIR             MORTRICIADIR + "camp/"

string inscr_str, ring_adj;
void inscript(string str);


void
update_descs()
{
	if (TO->query_adjs() == "gold")
	{
        remove_adj("iron");
        set_short("gold ring");
	}
}
		
void
create_terel_armour()
{
   set_name("ring");
   set_short("iron ring");
   set_adj("iron");
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 50);
   
   inscript("Love, Tecla.");
    set_armour_size(ANY_SIZE);
   
   set_default_armour(1, A_FINGERS, 0, 0);
   add_prop(OBJ_I_VALUE, 1);
   
   set_alarm(0.5, 0.0, update_descs);
}

void
inscript(string str)
{
   string intro, adj;
   
   adj = this_object()->query_adj();
   intro = "It's "+LANG_ADDART(adj)+
       " ring with an inscription which reads:\n";
   TO -> set_long(intro + "    " + str + "\n");
   inscr_str = str;
   ring_adj = adj;
}

string
query_recover()
{
    string s;

    if (!query_prop("q_solver")) return "";
    if (query_prop("q_solver") != TP->query_name()) return "";

    s = MASTER + ":";                       /* std arg */
    s += TO->query_prop("q_solver") + "#";  /* arg 1   */
    s += TO->query_prop("q_number") + "#";  /* arg 2   */
    s += ring_adj + "#" + inscr_str + "#";  /* arg 3&4 */
    s += TO->query_prop(OBJ_I_VALUE);       /* arg 5   */
    s += "#"+TO->query_prop("q_step");      /* arg 6   */

    return s;
}

void
init_recover(string arg)
{
    string s1, s3, s4;
    int i2, i5, i6;

    if (!arg) return;
    if (sscanf(arg, "%s#%d#%s#%s#%d#%d", s1,i2,s3,s4,i5,i6) != 6) {
        remove_object();
    } else {
	if (s1) add_prop("q_solver", s1);
	if (i2 > 0) add_prop("q_number", i2);
	set_adj(s3);
	inscript(s4);
	change_prop(OBJ_I_VALUE, i5);
        if (i6 >= 0) add_prop("q_step", i6);
    }
}
