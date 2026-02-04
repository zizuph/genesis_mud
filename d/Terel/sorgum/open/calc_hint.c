/*
 * calc_hint: based on the players name and the index, a fix number
 * from 0..11 is returned
 */
int
calc_hint(int index) {
    string *nam;
    int seed,i;

    nam = explode(this_player()->query_name(),"");
    seed = 3;
    for (i=0; i<sizeof(nam); i++)
	seed += i*97*(nam[i][0]-32);
    for (i=0; i<(17+index); i++) seed = random(32760,seed);
    return(random(12,seed));
}
