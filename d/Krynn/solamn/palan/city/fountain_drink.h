
/* Function for drinking water from the fountain */

string
drink_water()
{
    if ( TP->drink_soft(TP->drink_max() / 16, 0) )
    {
        write("You drink some water from from the fountain. It's cold " +
            "and refreshing.\n");
        say(QCTNAME(TP) + " drinks some water from the fountain.\n");
        
        return "";
    }
    else
        write("You are full and cannot drink any more.\n");
    
    return "";
}
