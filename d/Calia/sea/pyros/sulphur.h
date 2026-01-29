
int
do_scrape(string str)
{
    object sulphur;
    int num;

    if (str != "sulphur")
    {
        NF("What?\n");
        return 0;
    }
    if (!sizeof(TP->query_weapon(-1)))
    {
        write("You must be wielding a weapon to do that!\n");
        return 1;
    }
    sulphur = clone_object("/d/Calia/walkers/fire/objects/sulphur");
    num = 3 + random(6);
    sulphur->set_heap_size(num);
    sulphur->move(TP,1);
    write("You scrape "+num+" handfuls of yellow powder from the block of sulphur.\n");
    say(QCTNAME(TP)+" scrapes some powder off of the yellow block.\n");
    return 1;
}
