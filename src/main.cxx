
#include <iostream>
#include <string>
#include <vector>

#include "MathLexer.hxx"
#include "MathParser.hxx"
#include "MathAST.hxx"
#include "MathEvaluate.hxx"

int main(void){
	std::cout << "TESTING" << std::endl;
	std::cout << "  q to Quit" <<std::endl;
	while(true){
		std::string expr;
		std::getline(std::cin, expr);
		if(expr.c_str()[0] == 'q'){
			break;
		}
		std::optional<std::vector<std::string>> token = MathLexer::lex_string(expr);
		if(token.has_value()){
			if( !MathLexer::validate_expressions(*token)){
				std::cerr << "Invalid Token Where Found" << std::endl;
				continue;
			}
			MathLexer::fold_tokens(*token);

			MathParser p = MathParser();
			p.set_tokens(&*token);
			Node *node = p.run();

			if(!node){
				continue;
			}
			SafeValue val = evaluate(node);
			std::string answer = (val.num_type == NumType::I64)? std::to_string(val.i64) : std::to_string(val.f64);
			std::cout << "Answer: " << answer << "\n";
			delete node;

		}else{
			std::cerr << "Invalid Token Where Found" << std::endl;
		}

	}

	std::cout << "Run Successfull" << std::endl;
	return 0;
}
