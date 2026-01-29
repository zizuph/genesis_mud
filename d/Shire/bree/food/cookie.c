/* Cookies for Shire Inns 
 * Taveren, January 2001
 * Updated to a large cookie
 * -- Finwe, October 2005
 */

inherit "/std/food";

void
create_food()
{
    set_name("cookie");
    set_pname("cookies");
    set_short("large cookie");
    set_pshort("large cookies");
    set_long("This is a large cookie. It is square shaped and still warm. " +
        "The cookie looks delicious.\n");
    set_amount(50);
  
}
