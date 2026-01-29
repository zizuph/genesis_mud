        i = -1;
        size2 = sizeof(ctants2);
        while (++i < size2)
        {    
            size = sizeof(attackers[i]);
            verb = " is ";
            if (size >= 2)
                verb = " are ";
            write(capitalize(COMPOSITE_LIVE(attackers[i])) + verb + 
                "fighting " + ctants2[i]->query_name() + ".\n");
        }
