(setq result '())
(defun insert-n (list number index)
    (if (= index 0)
        (progn
            (setq result (append result (list number)))
            (if (null (car list))()
            (setq result (append result list))
            )
            (return-from insert-n result)
        ) 
        (progn
            (setq result (append result (list (car list))))
            (if (null (car list))()
            (insert-n (cdr list) number (- index 1))
            )
        )
    )
)


(write (insert-n (list 8 6 17 255 24 31) 983 4))