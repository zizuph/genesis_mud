status truth;
mixed return_value;
object *body_rule_list;

function funct;

void set_function(function new_funct)
{
    funct = new_funct;
}

void set_truth(status new_truth)
{
    truth = new_truth;
}

status query_truth()
{
    return truth;
}

void set_return_value(mixed new_return_value)
{
    return_value = new_return_value;
}

mixed query_return_value()
{
    return return_value;
}

void set_body_rule_list(object *new_body_rule_list)
{
    body_rule_list = new_body_rule_list;
}

object *query_body_rule_list()
{
    return body_rule_list;
}
