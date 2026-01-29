/* Special for house stewards Shire Inns
 * Taveren, January 2001
 *
 * Emotes & add items
 * Raymundo, Jan 2020
 */

inherit "/std/drink";

void
create_drink()
{
     	string adj1 = "house";
 	string adj2 = "special";
	string name = "drink";
	
      set_name(name);
	  add_name("special");
      add_adj(adj1);
	  add_adj(adj2);
      set_short(adj1 + " " + adj2 + " " + name);
      
      set_long("This " + query_short() + " looks like the bartender took "
		+ "a little of this and a little of that and a little of whatever "
		+ "people left in their glasses and dumped it all in a bucket, then "
		+ "swirled it around with a dirty spoon and poured it in your glass. "
		+ "It's the type of thing you'd normally see served to dwarven "
		+ "men on their way home from the mines, when they don't care "
		+ "what the drink is as long as it's cold and strong.\n");
		
      set_adj("glass");
	  
	  add_item("glass", "The glass is short and stout, about the size of a "
		+ "dwarf's closed fist.\n");
	  
	  set_drink_msg("Ooooh, that tasted foul! But you could feel the "
		+ "alcohol burn all the way down to your toes!\n");
	  
      set_soft_amount(150);
      set_alco_amount(33);
 
}                             