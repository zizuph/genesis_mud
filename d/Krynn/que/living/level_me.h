    switch (j)
    {
    case 1: set_adj("weak");
            break;
    case 2: set_adj("small");
            break;
    case 3: set_adj("average");
            break;
    case 4: set_adj("strong");
            break;
    case 5: set_adj("muscular");
            break;
    case 6: set_adj("powerful");
            break;
    case 7: set_adj("tough");
            break;
    case 8: set_adj("lethal");
            break;
    }

    /* different descriptions for the different levels! */
    switch (j) 
    {
    case 1: str = "He doesn't look very threatening.";
            break;
    case 2: str = "He looks threatening.";
            break;
    case 3: str = "You better not mess with him.";
            break;
    case 4: str = "He looks like he is a good fighter.";
            break;
    case 5: str = "He looks like he is a very good fighter.";
            break;
    case 6: str = "He seems to be able to kill you easily.";
            break;
    case 7: str = "He looks like he is an extremely good fighter.";
            break;
    case 8: str = "He looks like he can crush you in no time!";
            break;
    }

    seteuid(getuid(TO));

