#include "utilities.h"
#include "cool-parse.h"

extern Classes parse_results;
extern Program ast_root;
extern IdTable idtable;
extern IntTable inttable;
extern StrTable stringtable;

typedef struct {
    Symbol* name_of_class;
    IdTable class_idtable;
} class_tables;

IdTable my_table;

void check(Expression First, Expression Second, class__class* cls) 
{
    auto f_type = First;
    if (dynamic_cast<int_const_class*>(First) != nullptr) {
        f_type = dynamic_cast<int_const_class*>(First);
        if (dynamic_cast<int_const_class*>(Second) == nullptr)
            std::cerr << "Error: Invalid type conversion at class \"" << cls->get_name()->get_string()
                      << "\" at file " << cls->get_filename()->get_string() << ':' << cls->get_line_number() << '\n';
    }
    if (dynamic_cast<string_const_class*>(First) != nullptr) {
        f_type = dynamic_cast<string_const_class*>(First);
        if (dynamic_cast<string_const_class*>(Second) == nullptr)
            std::cerr << "Error: Invalid type conversion at class \"" << cls->get_name()->get_string()
                      << "\" at file " << cls->get_filename()->get_string() << ':' << cls->get_line_number() << '\n';

    }
    if (dynamic_cast<bool_const_class*>(First) != nullptr) {
        f_type = dynamic_cast<bool_const_class*>(First);
        if (dynamic_cast<bool_const_class*>(Second) == nullptr)
        std::cerr << "Error: Invalid type conversion at class \"" << cls->get_name()->get_string()
                  << "\" at file " << cls->get_filename()->get_string() << ':' << cls->get_line_number() << '\n';

    }
}

void full_types_checker(Expression expr_check, class__class* cls, IdTable table) 
{
    if (dynamic_cast<no_expr_class*>(expr_check) != nullptr)
        return;
    if (dynamic_cast<assign_class*>(expr_check) != nullptr)
    {
        auto assing_class_test = dynamic_cast<assign_class*>(expr_check);
        if (table.lookup_string(assing_class_test->get_name()->get_string()) != nullptr) 
        {
            std::cerr << "Error: Variable \"" << assing_class_test->get_name()->get_string() 
                      << "\" was declared at" << cls->get_filename()->get_string() << ':' 
                      << cls->get_line_number() << " this scope \n";
        }
        full_types_checker(assing_class_test->get_expr(), cls, table);
        return;
    }
    if (dynamic_cast<cond_class*>(expr_check) != nullptr)
    {
        auto cond_expr_test = dynamic_cast<cond_class*>(expr_check);
        full_types_checker(cond_expr_test->get_pred(), cls, table);
        full_types_checker(cond_expr_test->get_then_expr(), cls, table);
        full_types_checker(cond_expr_test->get_els_expr(), cls, table);
        return;
    }
    if (dynamic_cast<loop_class*>(expr_check) != nullptr)
    {
        auto loop_expr_test = dynamic_cast<loop_class*>(expr_check);
        full_types_checker(loop_expr_test->get_pred(), cls, table);
        full_types_checker(loop_expr_test->get_body(), cls, table);
        return;
    }
    if (dynamic_cast<let_class*>(expr_check) != nullptr)
    {
        auto let_expr_test = dynamic_cast<let_class*>(expr_check);
        full_types_checker(let_expr_test->get_init(), cls, table);
        full_types_checker(let_expr_test->get_body(), cls, table);
        return;
    }
    if (dynamic_cast<plus_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<plus_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if(dynamic_cast<sub_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<sub_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<mul_class*>(expr_check) != nullptr)
    {                    
        auto for_expr_test = dynamic_cast<mul_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<divide_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<divide_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<lt_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<lt_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<eq_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<eq_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<leq_class*>(expr_check) != nullptr)
    {
        auto for_expr_test = dynamic_cast<leq_class*>(expr_check);
        auto First = for_expr_test->get_first();
        auto Second = for_expr_test->get_second();
        check(First, Second, cls);
        return;
    }
    if (dynamic_cast<object_class*>(expr_check) != nullptr) {
        auto obj_class_test = dynamic_cast<object_class*>(expr_check);
        if (table.lookup_string(obj_class_test->get_name()->get_string()) == nullptr)
            std::cerr << "Error: Object \"" << obj_class_test->get_name()->get_string() 
            << "\" not found at" << cls->get_filename()->get_string() << ':'
            << cls->get_line_number() <<  "this scope \n";
    }
    if (dynamic_cast<isvoid_class*>(expr_check) != nullptr) {
        full_types_checker((dynamic_cast<isvoid_class*>(expr_check))->get_expr(), cls, table);
        return;
    }
    if (dynamic_cast<new__class*>(expr_check) != nullptr) {
        if (table.lookup_string((dynamic_cast<new__class*>(expr_check))->get_name()->get_string()) == nullptr)
        {
            std::cerr << "Error: Could not find class \"" << 
            (dynamic_cast<new__class*>(expr_check))->get_name()->get_string() << "\" at this scope " 
            << cls->get_filename()->get_string() << ':' << cls->get_line_number() <<  "\n";
        }
        return;
    }
    if (dynamic_cast<dispatch_class*>(expr_check) != nullptr) {
        if (table.lookup_string((dynamic_cast<dispatch_class*>(expr_check))->get_name()->get_string()) == nullptr)
        {
            std::cerr << "Error: Could not find class with method \"" << 
            (dynamic_cast<dispatch_class*>(expr_check))->get_name()->get_string() << "\" at this scope " 
            << cls->get_filename()->get_string() << ':' << cls->get_line_number() <<  "\n";
        }
        for (int i = 0; (dynamic_cast<dispatch_class*>(expr_check))->get_expr_act()->more(i); i++)
        {
            auto disp_expr_check = (dynamic_cast<dispatch_class*>(expr_check))->get_expr_act();
            for (int j = 0; disp_expr_check->more(j); j++)
            {
                auto inner_disp_expr_check = dynamic_cast<Expression_class*>(disp_expr_check->nth(j));
                full_types_checker(inner_disp_expr_check, cls, table);
            }
        }
        return;
    }
    if (dynamic_cast<static_dispatch_class*>(expr_check) != nullptr) {
        if (table.lookup_string((dynamic_cast<static_dispatch_class*>(expr_check))->get_name()->get_string()) == nullptr)
        {
            std::cerr << "Error: Could not find class with method \"" << 
            (dynamic_cast<static_dispatch_class*>(expr_check))->get_name()->get_string() << "\" at this scope " 
            << cls->get_filename()->get_string() << ':' << cls->get_line_number() <<  "\n";
        }
        for (int i = 0; (dynamic_cast<static_dispatch_class*>(expr_check))->get_expr_act()->more(i); i++)
        {
            auto disp_expr_check = (dynamic_cast<static_dispatch_class*>(expr_check))->get_expr_act();
            for (int j = 0; disp_expr_check->more(j); j++)
            {
                auto inner_disp_expr_check = dynamic_cast<Expression_class*>(disp_expr_check->nth(j));
                full_types_checker(inner_disp_expr_check, cls, table);
            }
        }
        return;
    }
}

void semant() {
    bool have_main = false;
    auto cand = static_cast<program_class*>(ast_root);
    auto test = cand->get_programm_classes();
    auto classes = dynamic_cast<class__class*>(cand->get_programm_classes());
    for(int i = test->first(); test->more(i); i = test->next(i)){
        auto subject = dynamic_cast<class__class*>(test->nth(i));
        Features n_features = subject->get_features();
        // Unique ID check
        if (my_table.lookup_string(subject->get_name()->get_string())) {
            std::cerr << "Error: Class \"" << subject->get_name()->get_string() <<
                         "\" is not a unique name for class at " << 
                         subject->get_filename() << ":" << subject->get_line_number() << '\n';
        }
        my_table.add_string(subject->get_name()->get_string());
        // parents check
        if (!subject->get_parent()->equal_string("Object", 6)) {
            auto parent_check = subject->get_parent();
            IdTable inner_table;
            for (int j = i ; j >= 0; j--) {
                class__class* parentis = dynamic_cast<class__class*>(test->nth(j));
                if (parentis->get_parent() == parent_check) 
                {
                    if (parentis->get_parent()->equal_string("Object", 6))
                    {
                        break;
                    }
                    else
                    {
                        if (inner_table.lookup_string(parentis->get_parent()->get_string()) != nullptr) {
                            std::cerr << "Error: No cycle inherits allowed at class \"" << parentis->get_parent()->get_string() << "\" at " <<
                                          subject->get_filename() << ":" << subject->get_line_number() << '\n';
                        }
                        parent_check = parentis->get_name();
                        inner_table.add_string(parentis->get_name()->get_string());
                        parentis = dynamic_cast<class__class*>(test->nth(j));
                        j = i;
                    }
                }
                if (j == 0) {
                    std::cerr << "Error: Could not find parents classes to \"" << subject->get_parent()->get_string() << "\" at " <<
                                  subject->get_filename() << ":" << subject->get_line_number() << '\n';
                    break;
                }
            }
        }
        // прикрутить сюда dispatch также может здесь следует проверять область видимости и т.д.
        // проверка 15 классов... это будет много if-ов с dynamic_cast, может я просто упускаю что-то?
        for (int i = n_features->first(); n_features->more(i); i = n_features->next(i))
        {   
            auto type_check = dynamic_cast<method_class*>(n_features->nth(i));
            if (type_check != nullptr) {
                auto feature_on_check = dynamic_cast<method_class*>(n_features->nth(i));
                auto test_feature = feature_on_check->get_name();
                if (test_feature->equal_string("main", 4))
                    have_main = true;
                if (my_table.lookup_string(test_feature->get_string()) != nullptr)
                {
                    std::cerr << "Error: Not unique feature name " << '\"' << test_feature->get_string() << '\"' <<
                                " at " << subject->get_filename() << ":" << subject->get_line_number() << '\n';
                }
                auto expr_check = feature_on_check->get_expr();
                my_table.add_string(test_feature->get_string());
                full_types_checker(expr_check, subject, my_table);
                if (feature_on_check->get_formals() != nullptr)
                {
                    auto formals_check = dynamic_cast<Formals>(feature_on_check->get_formals());
                    for (int i = formals_check->first(); formals_check->more(i); i = formals_check->next(i))
                    {
                        auto inner_formal = dynamic_cast<formal_class*>(formals_check->nth(i));
                        if (my_table.lookup_string(inner_formal->get_name()->get_string()) == nullptr) 
                        {
                            std::cerr << "Error: No such ID found " << '\"' << test_feature->get_string() << '\"' <<
                                         " at " << subject->get_filename() << ":" << subject->get_line_number() << '\n';
                        }
                    }
                }
            }
            else
            {
                auto n_attr = dynamic_cast<attr_class*>(n_features->nth(i));
                auto test_attr = n_attr->get_name();
                my_table.lookup_string(subject->get_parent()->get_string());
                if (my_table.lookup_string(test_attr->get_string()) != nullptr)
                    std::cerr << "Error: Variable \"" << test_attr->get_string() << "\" was declared before " 
                              << subject->get_filename()->get_string() << ':' << subject->get_line_number();
                if (my_table.lookup_string(test_attr->get_string()) != nullptr) {
                    std::cerr << "Error: Not unique attribute name \"" << test_attr->get_string() << '\"' << " at "
                              << subject->get_filename() << ":" << subject->get_line_number() << '\n';
                }
                // my_table.add_string(test_attr->get_string());
            }
        }
    }
    if (!have_main) {
        std::cerr << "Error: Could not find \"main\" method in any class\n";
    }
}