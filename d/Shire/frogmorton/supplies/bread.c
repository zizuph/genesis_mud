/* Bread for Shire Inns
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Fixed up a little. */

inherit "/std/food";

void
create_food()
{
      set_name("bread");
      //add_name("slice of bread");
      add_name("slice of bread", 1);
      //add_name("slice of bread and jam");
      add_name("slice of bread and jam", 1);
      set_pname("bread");
      add_pname("slices of bread");
      add_pname("slices of bread and jam");
      set_short("slice of bread and jam");
      set_pshort("slices of bread and jam");
      //set_long("This is a slice of frsh bread. It is " +
      set_long("This is a slice of fresh bread. It is " +
        "buttered and covered with fresh jam.\n");
      set_amount(100);
}
