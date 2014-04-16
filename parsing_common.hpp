/** parsing_common.hpp
 * 
 * Functions to parse, which need a few different conflicting types
 * 
 * Includes:
 *   token.hpp
 *   expr_tree.hpp
 * */ 
 
#ifndef _PARSING_COMMON_HPP_
#define _PARSING_COMMON_HPP_

#include "token.hpp"
#include "expr_tree.hpp"

namespace expr_tree {
	
Expr_tree& parse_to_Expr_tree(token::list_Token& lst);

} // namespace expr_tree


namespace token {
	
list_Token& parse_to_Token_list(string str);

}// namespace token

#endif // _PARSING_COMMON_HPP_

