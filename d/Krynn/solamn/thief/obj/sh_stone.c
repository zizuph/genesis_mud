/* created by Aridor, 10/94 */
/* Note: this sharpening stone works exactly like the knight tend skill.
 *       it even uses the same prop :)
 */

#include <composite.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#define KNIGHT_HITS "k_knight_hits"

inherit "/std/object";

void
create_object()
{
    set_name("whetstone");
    add_name("stone");
    set_adj("sharpening");
    add_adj("ordinary");
    set_short("@@my_short@@");
    set_long("@@my_long@@");
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, "@@my_value@@");
}

void
init()
{
    ADA("sharpen");
}

int
sharpen(string str)
{
    object *ob;
    int i, hits, dif, last;
    
    NF("Tend what?\n");
    if (!str)
      return 0;
    ob = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(ob))
      return 0;
    
    NF("You can only sharpen weapons.\n");
    ob = filter(ob, "filter_wep", TO);
    if (!sizeof(ob))
      return 0;
    NF("You can only sharpen weapons that have an edge or a tip.\n");
    ob = filter(ob, "filter_no_bludgeon", TO);
    if (!sizeof(ob))
      return 0;
    
    for (i = 0; i < sizeof(ob); i++)
      {
	  hits = ob[i]->query_weapon_hits();
	  if (hits < (last = ob[i]->query_prop(KNIGHT_HITS)) || !last)
	    ob[i]->add_prop(KNIGHT_HITS, hits);
	  else
	    {
		dif = hits - last;
		dif = dif / 2;
		dif = random(dif);
		hits -= dif;
		ob[i]->set_weapon_hits(hits);
		ob[i]->add_prop(KNIGHT_HITS, hits);
	    }
      }
    
    write("You sharpen " + COMPOSITE_DEAD(ob) + " skillfully with the " +
	  "whetstone.\n");
    say(QCTNAME(TP) + " sharpens " + QCOMPDEAD + " with something.\n");

    set_short("whetstone");
    set_long("This is a typical whetstone, used to sharpen weapons.\n");
    add_prop(OBJ_I_VALUE, 50);
    return 1;
}

int
filter_wep(object ob)
{
    if (ob->check_weapon())
      return 1;
    return 0;
}

int
filter_no_bludgeon(object ob)
{
    if (ob->query_dt() == 4)
      return 0;
    return 1;     
}

string
my_short()
{
    if (E(TO)->query_skill(SS_AWARENESS) > 21)
      return "whetstone";
    return "ordinary stone";
}

string
my_long()
{
    if (E(TO)->query_skill(SS_AWARENESS) > 21)
      return "This is a typical whetstone, used to sharpen weapons.\n";
    return "This is an ordinary looking stone. But it does have a strange " +
      "form, a little longish and it seems perfect to hold it. Just " +
	"what could it be for?\n";
}

int
my_value()
{
    if (E(TO)->query_skill(SS_AWARENESS) > 21)
      return 50;
    return 1;
}
