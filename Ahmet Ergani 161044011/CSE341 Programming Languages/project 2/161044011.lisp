(defun write-tokens(tokens name)        ;function that creates/opens the file and prints "; DIRECTIVE: print". then calls the recursive function
    (with-open-file (stream  name :external-format charset:iso-8859-1
        :direction :output
        :if-exists :overwrite           ;overwrite if the file already exists
        :if-does-not-exist :create )
        (format stream "; DIRECTIVE: print")    ;printing "; DIRECTIVE: print"
        (format stream "~%")
        (rec tokens stream)             ;calling the recursive function
    )
)

(defun rec(tokens stream)       ;recursive function that prints every token to the file
    (if (null (car tokens) )
        (return-from rec)
    )
    (format stream "(\"~D\" " (car (car tokens)))       ;type of the token
    (format stream "\"~D\")" (car (cdr (car tokens))))  ;token itself
    (format stream "~%")                                ;newline
    (rec (cdr tokens) stream)                           ;recursive call
)
;supposed result of lexer
(setq tokens '(("operator" "(") ("keyword" "deffun") ("identifier" "sumup") ("operator" "(") ("identifier" "x") ("operator" ")")
 ("operator" "(") ("keyword" "if") ("operator" "(") ("keyword" "equal") ("identifier" "x") ("literal" "0")
 ("operator" ")") ("literal" "1") ("operator" "(") ("operator" "+") ("identifier" "x") ("operator" "(")
 ("identifier" "sumup") ("operator" "(") ("operator" "-") ("identifier" "x") ("literal" "1") ("operator" ")")
 ("operator" ")") ("operator" ")") ("operator" ")") ("operator" ")"))
 )
(setq name "161044011.tree")        ;filename
(write-tokens tokens name)          ;calling the function