
string *a, *b;

void
create()
{
    a = ({ "og", "fo", "ni", "bur", "eht", "htiw", "tsud", "flesruoy",
	   "elkraps", "niatruc", "hguorht", "sdrawkcab", "ssenirartnoc"});
	   
    b = ({ "Lars", "Mrpr", "Tintin", "Nick", "Tricky", "Styles",
	   "Commander", "Ultimate", "Marvin", "Mort", "Starwine",
	   "Dworkin", "Fizban" });
}

string *
get_desc()
{
    string x, y;

    if (sizeof(a))
    {
        x = a[0];
        y = b[0];
        a = a[1..sizeof(a)];
        b = b[1..sizeof(b)];
        return ({ x, y });
    }
    return ({ "ymmud", "Padrone" });
}

void
return_desc(mixed desc)
{
    if (pointerp(a))
        a += ({desc[0]});
    else
        a = ({desc[0]});
    if (pointerp(a))
        b += ({desc[1]});
    else
        b = ({desc[1]});
}

int
remove_object()
{
    destruct();
    return 1;
}
