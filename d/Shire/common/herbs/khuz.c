/* 
 * This is Khuz. It improves a player's dis. 
 * It is based on the same herb by Theobald, Jan 24, 1995, originally 
 * from the old Rhovanion domain.
 * Updated by Finwe, May 2004
 * Fixed effect, Cotillion, 2015-04-02 
 */

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_herb()
{
    set_name("root");
    set_pname("roots");
    set_adj("twisted");
    add_adj("brown");
    set_short("twisted brown root");
    set_pshort("twisted brown roots");
    set_herb_name("khuz");
    set_id_long("This is a twisted brown root named Khuz. It is " +
        "multi-branched and very thick, and grows in woodlands and " +
        "meadows. The root is used by soldiers to gain courage in combat.\n");
    set_unid_long("This is twisted brown root.\n");

    set_id_diff(15);
    set_find_diff(5);
    set_effect(HERB_ENHANCING, "dis", 20);
    set_ingest_verb("eat");
    set_decay_time(1800);
    set_herb_value(850);
    set_dryable();
}
