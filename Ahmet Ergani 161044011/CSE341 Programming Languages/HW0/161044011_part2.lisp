(defun  merge-list(list1 list2)
    (setq list1(reverse list1))
    (setq list1 (cons (car list2) list1))
    (setq list1(reverse list1))
    (if (null (cdr list2) )
    	(return-from merge-list list1)
    	(merge-list list1 (cdr list2) )
    )
)
(write (merge-list(list 1 2 3) (list "A" (list "B" "D") "C")))