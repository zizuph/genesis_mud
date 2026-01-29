/*
 *  The book that decribes the wedding ceremony
 *							Tricky, Dec 1992
 */

inherit "/std/object";

void
create_object()
{
    set_name(({"book of wedlock", "thick book", "book"}));
    set_adj("thick");
    set_short("thick book");
    set_long("The thick book is labeled \"Book of Wedlock\".\n");
}

void
init()
{
    add_action("do_read", "read");
}

int
read(string str)
{
    if (!str)
	return 0;

    str = lower_case(str);

    if (id(str) || str == "index")
    {
	write("                 Book of Wedlock\n"
	    + "                    ---------\n"
	    + "                      INDEX\n"
	    + "\n"
	    + "     Chapter 1  ..........  Wedlock\n"
	    + "     Chapter 2  ..........  Things you need\n"
	    + "     Chapter 3  ..........  The ceremony\n");
	return 1;
    }
    if (str == "chapter 1")
    {
	write("Chapter 1 ................................. Wedlock\n"
	    + "\n"
	    + "When two people have strong loving feelings for each other\n"
	    + "they might consider to join themselves in holy matrimony,\n"
	    + "or holy wedlock as some say.\n"
	    + "\n"
	    + "The ceremonial wedding is performed by a high priestess\n"
	    + "who will charge money for it. It is essential that the\n"
	    + "ceremony is followed exactly. After the ceremony both\n"
	    + "persons obtain a wedding ring to keep the bonds between\n"
	    + "strong and vivid.\n");
	return 1;
    }
    if (str == "chapter 2")
    {
	write("Chapter 2 ................................. Things you need\n"
	    + "\n"
	    + "To perform a wedding the following people are needed:\n"
	    + "\n"
	    + "   - The high priestess; she will lead the ceremony\n"
	    + "   - The two people that want to be married\n"
	    + "   - Two witnesses, one for each of the marrying persons\n"
	    + "\n"
	    + "The following items are also essential:\n"
	    + "\n"
	    + "   - The wedding bouquet; the bride should carry it\n"
	    + "   - The wedding corsage; the groom should wear it\n"
	    + "   - The white sealring; the bride's witness should wear it\n"
	    + "   - The black sealring; the groom's witness should wear it\n"
	    + "\n"
	    + "The priestess should always be around, and the items can\n"
	    + "be found in the little cabinet next to the altar.\n"
	    + "Currently the price of the ceremony is 5000 cc.\n");
	return 1;
    }
    if (str == "chapter 3")
    {
	write("Chapter 3 ................................. The ceremony\n"
	    + "\n"
	    + "The ceremony performed has been designed to be as simple\n"
	    + "as possible. The priestess will ask clear questions to\n"
	    + "all people involved. They can say \"Yes\", \"I do\" or \"No\".\n"
	    + "All other replies are ignored, as are the things that other\n"
	    + "people say.\n"
	    + "Note that if any of the people involved denies one of the\n"
	    + "questions, the whole wedding will be cancelled. No refunds\n"
	    + "are given. So, think thoroughly about who you choose.\n");
	return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
