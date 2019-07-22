(setq Keywords '( "and" "or" "not" "equal" "append" "concat"
"set" "deffun" "for" "while" "if" "exit"))
(setq tokens-final '())
(defun read-file(filename)
	(with-open-file (stream filename)
		(loop for line = (read-line stream nil)
        	while line
        	collect line))
)

(defun is-operator(token)
	(if (equal token "+")
		(return-from is-operator t))
	(if (equal token "-")
		(return-from is-operator t))
	(if (equal token "/")
		(return-from is-operator t))
	(if (equal token "*")
		(return-from is-operator t))
	(if (equal token "+")
		(return-from is-operator t))
	(if (equal token "**")
		(return-from is-operator t))
	(return-from is-operator nil)
)

(defun is-keyword(token Keywords)
	(if (null (car Keywords))
		(return-from is-keyword nil))
	(if (string= token (car Keywords))
		(return-from is-keyword t))
	(is-keyword token (cdr Keywords))
)

(defun is-literal(token)
	(loop for i from 0 to (-(length token) 1)
   		do (if (char<= (char token i) #\9)
   				(if (char>= (char token i) #\0)
   					(setq i (+ i 1))
   					(return-from is-literal nil)
   				)
   				(return-from is-literal nil)
   			)
	)
	(return-from is-literal t) 
)

(defun tokenize-line(token tokens line i)
	(if (= (length line) i)
		(progn
			(if (equal 0 (length token))
			()
			(progn
				(if (is-literal token)
					(setq tokens(append tokens (list (list "literal" token))))
					(if (is-keyword token Keywords)
						(setq tokens(append tokens (list (list "keyword" token))))
						(if (is-operator token)
							(setq tokens(append tokens (list (list "operator" token))))
							(setq tokens(append tokens (list (list "identifier" token))))
						)
					)	
				)
				(setq token "")
			)
		)
			(return-from tokenize-line tokens))
		)
	(if (equal (subseq line i (+ i 1)) " ")
		(if (equal 0 (length token))
			()
			(progn
				(if (is-literal token)
					(setq tokens(append tokens (list (list "literal" token))))
					(if (is-keyword token Keywords)
						(setq tokens(append tokens (list (list "keyword" token))))
						(if (is-operator token)
							(setq tokens(append tokens (list (list "operator" token))))
							(setq tokens(append tokens (list (list "identifier" token))))
						)
					)	
				)
				(setq token "")
			)
		)
		(if (equal (subseq line i (+ i 1)) "(")
			(progn
			(if (equal 0 (length token))
				()
				(progn
				(if (is-literal token)
						(setq tokens(append tokens (list (list "literal" token))))
						(if (is-keyword token Keywords)
							(setq tokens(append tokens (list (list "keyword" token))))
							(if (is-operator token)
								(setq tokens(append tokens (list (list "operator" token))))
								(setq tokens(append tokens (list (list "identifier" token))))
							)
						)	
					)
					(setq token "")
				)
			)
				(setq tokens(append tokens (list (list "operator" "("))))
			)
			(if (equal (subseq line i (+ i 1)) ")")
				(progn
					(if (equal 0 (length token))
						()
						(progn
							(if (is-literal token)
							(setq tokens(append tokens (list (list "literal" token))))
								(if (is-keyword token Keywords)
								(setq tokens(append tokens (list (list "keyword" token))))
									(if (is-operator token)
										(setq tokens(append tokens (list (list "operator" token))))
										(setq tokens(append tokens (list (list "identifier" token))))
									)
								)	
							)
							(setq token "")
						)
					)
					(setq tokens(append tokens (list (list "operator" ")"))))
				)
				(setq token (concatenate 'string token (subseq line i (+ i 1))))
			)
		)	
	)
	(tokenize-line token tokens line (+ i 1))
)

(defun iteration(lines)
	(setq line (car lines))
	(setq line(string-trim '(#\Tab) line))
	;(write-line line)
	(setq tokens '())
	(let ((token ""))
	(setq tokens (tokenize-line token tokens line 0))
	)
	(write tokens)
	(write-line "")
	(if (null (cdr lines))
		(return-from iteration))
	(iteration (cdr lines)) 
)
(defun lexer(filename)
	(setq lines (read-file filename))
	(iteration lines)
) 

(lexer "example.txt")