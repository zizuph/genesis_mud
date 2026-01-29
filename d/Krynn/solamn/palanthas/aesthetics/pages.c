/*
 * Backroom of a Palanthian government building where pages
 * without a current assignment can hire out as messengers
 * for players.
 *
 * Smells?
 *
 * Mortis 05.2005
 *
 */

#include "../local.h"
#include CLOCKH
#include <money.h>
#include <macros.h>
#include <formulas.h>

inherit MONKS_ROOMBASE;

string
query_to_jail()
{
	return "northwest";
}

void
create_palan_room()
{
    SHORT("Backroom of a government building frequented by pages");
    LONG("This is a small backroom in one of the government buildings in "
	+ "Palanthas.  Several pages mill about relaxing and chatting.  Sparsely "
	+ "furnished with a few chairs and stools, the only other items you "
	+ "pick out are a table against the north wall upon which a paper sign "
	+ "has been propped.  An official government doorway leads east into "
	+ "the rest of the building, and Scholis Court is outside to the "
	+ "northwest.\n");

	ITEM(({"scholis court", "court"}), "The worn marble of Scholis "
	+ "court widens outside into an oval around which several buildings "
	+ "are situated, this being one of them.\n");
	ITEM(({"office", "brick office", "government office", "office building"}),
	  "You're here.  You made it.  Have a <look> around.\n");
	ITEM("doorway", "Authorized personnel come and go through the doorway "
	+ "to the east.  A pair of guards on the other side scrutinize those "
	+ "attempting to pass.\n");
	ITEM(({"guard", "guards"}), "You can only make out their silhouette "
	+ "through the doorway to the east, but outline of their platemail "
	+ "is unmistable.\n");
	ITEM(({"page", "pages"}), "Young pages in white mill about relaxing, "
	+ "chatting, and some even looking for things to do.\n");
	ITEM(({"chair", "chairs", "stool", "stools"}), "Simple, well-worn "
	+ "chairs and stools line the walls here for pages to relax upon.\n");
	ITEM(({"table", "sign"}), "A worn, wooden table sits against the "
	+ "north wall.  Atop it is a sign created from a folded piece of paper "
	+ "and black lettering done in the old style.  You may <read sign>.\n");
	ITEM(({"floor", "ceiling", "wall", "walls"}), "The floor is made of "
	+ "translucent white marble, the ceiling of large oak beams and planks, "
	+ "and the walls have been built from small, beige bricks.\n");

	CMD("sign", "read", "@@read_sign");
	CMD(({"page", "messenger"}), "hire", "@@hire_page");

	EXIT(MONKS + "gov_ofc", "east", "@@place_closed", 0);
	EXIT(MONKS + "a01", "northwest", 0, 0);

}

int
place_closed()
{
	write("A guard on the other side of the doorway says:  Whoa!  Government "
	+ "officials, Bureamancers, and pages only!\n");
	return 1;
}

int
read_sign()
{
	say(QCTNAME(TP) + " studies the paper sign on the table along the "
	+ "north wall.\n");
	write("The paper sign reads...\n");
	cat(MONKS + "obj/page_sign.txt", 1, 50);
	return 1;
}

int
hire_page()
{
	object apage;

	if (!MONEY_ADD(TP, -144))
	{
		write("A page says:  You're not going to have much luck finding a "
		+ "page to run messages for you for less than a gold.  You'd better "
		+ "come back with more money.\n");
		return 1;
	}

	write("You hire a page's services.\n");
	say(QCTNAME(TP) + " hires a page's services.\n");

	apage = clone_object(MONKS + "obj/messenger_page")->move(TP);

	return 1;
}
