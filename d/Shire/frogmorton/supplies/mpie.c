/* meat pie for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Fixed up a little.
 */

inherit "/std/food";

void
create_food()
{
    //set_name("meat");
    set_name("pie");
    set_adj("meat");
    //add_name("pie");
    //set_pname("meat");
    //add_pname("pies");
    //set_short("meat pie");
    //set_pshort("meat pies");
    set_long("This meat pie is full of chunks of brown " +
        "meat, vegetables, and a thick broth. The crust is " +
        "golden brown.\n");
    set_amount(375);
         
}     
