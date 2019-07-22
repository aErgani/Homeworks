(setq result '())
(defun List-leveller(list1)
	(write list1)
	(write-line "")
	(if (atom (car list1))
		(progn
			(write-line "appended")	
			(setq result (append result (list (car list1))))
		)
		(progn
			(write-line "nested detected")	
			(List-leveller (car list1))
		)	
	)
	(if (null (cdr list1)) 
		(progn
			(write-line "no cdr remaining")	
			(return-from List-leveller result)
		)
		(progn
			(write-line "usual")	
			(List-leveller (cdr list1))
		)
	)
)
(write (List-leveller (list 1 2 (list 3 (list 4 5 ) 6 (list 7 25) 8 ) 9 )))

