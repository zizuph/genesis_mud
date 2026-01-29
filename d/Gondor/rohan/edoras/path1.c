inherit "/d/Gondor/common/lib/town";

create_room() {
    hillside = "east";
    height = 1;
    road = 1;
    density = 1;
    extraline ="The city wall, which is circling the whole town of Edoras at the bottom of the hill, is to the east, and right beside it lies a cosy little inn. There is a field to the east, where the men of Rohan feed their horses in time of trouble. The street winds some upwards towards the gates to the northwest and southwest towards a little square. ";
    make_the_room();
    add_exit("/d/Gondor/rohan/edoras/field","east",0);
/*    add_exit("/d/Gondor/rohan/edoras/lsinn","east",0,0);*/
    add_exit("/d/Gondor/rohan/edoras/ingate","northwest",0);
    add_exit("/d/Gondor/rohan/edoras/well","southwest",0);
}
