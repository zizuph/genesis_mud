/* 
 * Food for AA mess hall
 * Finwe, February 2019
 */

inherit "/std/food";

void
create_food()
{
    add_name("stew");
    set_name("beef");
    set_short("steaming bowl of beef stew");
    set_pshort("steaming bowls of beef stews");
    set_adj(({"steaming", "bowl"}));
    set_long("his " +
	"is a steaming hot bowl of brown mushy stuff. It smells vaguely " +
	"of beef and doesn't look terribly appetizing.\n");
    set_amount(95);
}
