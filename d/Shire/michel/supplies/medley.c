/* Magic Medley
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("medley");
    set_pname("medleys");
    set_short("big meat medley");
    set_pshort("big meat medleys");
    set_adj("meat");
    add_adj("big");
    set_long("The medley is composed of several varieties "+
      "of meat, including vension, beef, and rabbit, all marinated "+
      "in Dolin's secret sauce for days while roasting in a bronze "+
      "pot over a bed of hot hickory coals. Even the largest "+
      "man to come through Michel Delving can fill up on this "+
      "collection of luscious meats, although few hobbits "+
      "from this area can even finish one.\n");
     set_amount(575);
     
}
