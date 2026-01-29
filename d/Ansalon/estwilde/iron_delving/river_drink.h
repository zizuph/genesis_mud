string
drink_water()
{
    if(TP->drink_soft(TP->drink_max() /16, 0))
    {
	write("You kneel down and take a drink from the bubbling stream.\n");
	say(QCTNAME(TP) + " kneels down and takes a drink from " +
	  "the bubbling stream.\n");
	return "";
    }
    else
	write("You are full of water.\n");
    return "";
}
