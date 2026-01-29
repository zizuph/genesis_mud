/* Mincemeat pie for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Fixed up a little.
 */

inherit "/std/food";

void
create_food()
{
    //set_name("mincemeat");
    set_name("pie");
    set_adj("mincemeat");
    //add_name("pie");
    //set_pname("mincemeat");
    //add_pname("pies");
    //set_short("mincemeat pie");
    //set_pshort("mincemeat pies");
    set_long("This pie is a mixture of finely chopped " +
//        "apples, aromatic spices, amnd chopped rabbit meat in a " +
        "apples, aromatic spices, and chopped rabbit meat in a " +
        "broth.\n");
    set_amount(575);
         
}     
    
