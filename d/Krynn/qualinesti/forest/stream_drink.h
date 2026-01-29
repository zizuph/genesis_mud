/* Function for drinking water from the stream. */

drink_water()
{
    if ( TP->drink_soft(TP->drink_max() / 16, 0))
    {
        write("You kneel down and drink some water from the stream. You " +
            "feel refreshed.\n");
        say(QCTNAME(TP) + " kneels down and drinks some water from the " +
            "stream.\n");
        
        return "";
    }
    else
        write("You can not drink any more.\n");
    
    return "";

}
        