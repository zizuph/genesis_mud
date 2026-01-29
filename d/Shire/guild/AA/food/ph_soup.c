/* 
 * Food for AA mess hall    
 * Finwe, February 2019
 */

inherit "/std/food";

void
create_food()
{
    add_name("soup");
    set_name("pheasant");
    set_short("bowl of pheasant soup");
    set_pshort("bowls of pheasant soup");
    set_adj(({"thick", "rich"}));
    set_long("This is a bowl of fairly decent-looking pheasant soup..\n");
    set_amount(180);
}
