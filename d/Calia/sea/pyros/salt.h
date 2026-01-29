
int
do_scrape(string str)
{
    object salt;
    int num;

    if (str != "salt")
    {
        NF("What?\n");
        return 0;
    }
    if (!sizeof(TP->query_weapon(-1)))
    {
        write("You must be wielding a weapon to do that!\n");
        return 1;
    }
    salt = clone_object("/d/Calia/walkers/fire/objects/salt");
    num = 3 + random(6);
    salt->set_heap_size(num);
    salt->move(TP,1);
    write("You scrape "+num+" handfuls of salt from the walls and ceiling.\n");
    say(QCTNAME(TP)+" scrapes some salt off the walls and ceiling.\n");
    return 1;
}
