/* Object to evaluate simple arithmetic expressions held in strings.
   Expressions should contain only dyadic operators (two arguments)
   + - * and /, and of course arbitrary nesting of brackets is allowed.
   Numbers should be positive integers.

   Maniac
*/

inherit "/std/object";
#include <stdproperties.h>
#include "specials.h"

int *numbers = ({ });


int
is_digit(string expr)
{
    if (expr >= "0" && expr <= "9") 
        return 1;
    else
        return 0; 
}


int
is_number(string expr)
{
    int i;

    for (i = 0; i < strlen(expr); i++)
        if (!is_digit(extract(expr, i, i)))
             return 0;
    return 1;
}


/* returns 1 if string is an op, 0 if not
*/
int
is_op(string str)
{
    if ((str == "+") || (str == "-") ||
        (str == "*") || (str == "/"))
        return 1;
    else
        return 0;
}




/* returns the next possible split of for the given expression of the form
   a op b where a and b are well formed sub-expressions.
   The split takes the form: ({ subexpr1, subexpr2, operator }). 
*/
string *
get_next_split(string expr)
{
    string e1, e2, op, e3;
    int p_depth;

    p_depth = 0;
    e1 = "";
    e2 = expr;
    op = "";
    e3 = "";

    while ((op == "") && strlen(e2))  {
        e3 = extract(e2, 0, 0);
        if ((p_depth == 0) && is_op(e3))
            op = e3;
        else
            e1 += e3;
        if (e3 == "(") p_depth++;
        else if (e3 == ")") p_depth--;
        if (strlen(e2) > 1)
            e2 = extract(e2, 1, strlen(e2)-1);
        else
            e2 = "";
    }
     
    return ({ e1, e2, op });
}




/* returns for a given expression all possible splits of the form a op b
   where a and b are well formed sub-expressions.
   Each split takes the form: ({ subexpr1, subexpr2, operator }).
*/
mixed
splits_of(string expr)
{
    mixed splits = ({ });
    string *next_split = ({ });
    string *a_split = ({ });

    next_split = ({ "", expr, "" }); 
    while (strlen(next_split[1])) {
        a_split = get_next_split(next_split[1]);
        next_split = ({ next_split[0]+next_split[2]+a_split[0], 
                        a_split[1], a_split[2] });
        if (strlen(next_split[1])) splits += ({ next_split });
    }
    return splits;
}




/* returns 1 if the expression is of the form a op b where a and b
   are well formed sub-expressions.
*/
int
can_split(string expr)
{
    string e1, e2; 

    if (sizeof(splits_of(expr))) 
        return 1;
    else
        return 0; 
}




/* returns precedence of an op 
*/
int
prec(string op)
{
    switch (op) {
        case "+": 
            return 0;
            break;
        case "-":
            return 1;
            break;
        case "*":
            return 2;
            break;
        case "/":
            return 3;
            break;
        default:
            return 4;
    }
}


/* Return by reference the array containing the split of lowest  
   precedence in the arithmetic string expression. Array is of the
   form ({ subexpr1, subexpr2, operator }).
   Assumption made that the string is splitabble.
*/
string *
correct_split(string expr)
{
    string *correct_split = ({"", "", "" });
    mixed splits;
    int i;

    splits = splits_of(expr);
    for (i = sizeof(splits)-1; i >= 0; i--) 
        if (prec(splits[i][2]) < prec(correct_split[2])) 
             correct_split = splits[i];

    return correct_split;
}


/* prototype */
mixed eval(string expr);

/* Returns 1 if we can remove the outer brackets to yield 
   a legal expression, 0 otherwise */
int
can_remove_brackets(string expr)
{
    int *nums = numbers;
    if ((expr[0] == '(') && (expr[strlen(expr)-1] == ')')) 
        if (eval(extract(expr, 1, strlen(expr)-2)) == "fail") {
             numbers = nums;
             return 0;
        }
        else {
             numbers = nums;
             return 1;
        }
    else {
        numbers = nums;
        return 0;
    }
}


/* evaluate an arithmetic expressions, returning the answer */
mixed 
eval(string expr)
{
    int i;
    mixed v, v1, v2;
    string cexpr, nexpr; 
    string *res;

    if (!expr || (extract(expr, 0, 0) == ")")) return "fail";

    cexpr = ""; nexpr = "";

    /* Clean string of spaces */
    for (i=0; i < strlen(expr); i++)
        if (expr[i] != 32)
            cexpr += strchar(expr[i]);

    /* Main evaluation if..then */
    if (is_number(cexpr)) {
        numbers += ({ atoi(cexpr) });
        return atoi(cexpr);
    }
    else if (can_remove_brackets(cexpr)) {
        nexpr = extract(cexpr, 1, (strlen(cexpr)-2));
        return eval(nexpr);
    }
    else if (can_split(cexpr)) {
        res = correct_split(cexpr);
        v1 = eval(res[0]); 
        v2 = eval(res[1]);
        if (v1 == "fail" || v2 == "fail") return "fail";
        switch (res[2]) {
            case "+":
                v = v1 + v2;
                break;
            case "-":
                v = v1 - v2;
                break;
            case "*":
                v = v1 * v2;
                break;
            case "/":
                if (v2 == 0) return "fail";
                v = v1 / v2;
                break; 
            default:
                v = "fail";
                break;
        }
        return v; 
    }
    else return "fail";
}


/* Return the evaluation result and the numbers used */
mixed *
eval_plus(string expr)
{
    int *nums;
    mixed result;

    result = eval(expr);
    nums = numbers;
    numbers = ({ });
    return ({ result, nums }); 
}


void
create_object()
{
    set_name("evaluator");
    set_adj("maniacal");
    set_short("maniacal evaluator");
    set_long("A simple evaluator to calculate the integer value of " +
             "an arithmetic expression held in a string.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

int
do_eval(string expr)
{
    mixed *result;
    string str = "";
    int i;

    result = eval_plus(expr);
    
    str += ("Result: " + result[0] + ".\n" + "Numbers: "); 
    for (i=0; i < sizeof(result[1]); i++)
        str += ("" + result[1][i] + ", ");
    str += ".\n";
    this_player()->catch_msg(str);
    return 1;
}

void
init()
{
    ::init();
    add_action("do_eval", "eval");
}

