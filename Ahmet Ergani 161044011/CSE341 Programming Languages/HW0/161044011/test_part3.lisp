(load "csv-parser.lisp")
(in-package :csv-parser)

;; (read-from-string STRING)
;; This function converts the input STRING to a lisp object.
;; In this code, I use this function to convert lists (in string format) from csv file to real lists.

;; (nth INDEX LIST)
;; This function allows us to access value at INDEX of LIST.
;; Example: (nth 0 '(a b c)) => a

;; !!! VERY VERY VERY IMPORTANT NOTE !!!
;; FOR EACH ARGUMENT IN CSV FILE
;; USE THE CODE (read-from-string (nth ARGUMENT-INDEX line))
;; Example: (mypart1-funct (read-from-string (nth 0 line)) (read-from-string (nth 1 line)))

;; DEFINE YOUR FUNCTION(S) HERE
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


;; MAIN FUNCTION
(defun main ()
  (with-open-file (stream #p"input_part3.csv")
    (loop :for line := (read-csv-line stream) :while line :collect
      (format t "~a~%"
      ;; CALL YOUR (MAIN) FUNCTION HERE
      (progn
      (setq result '())      
      (insert-n (read-from-string (nth 0 line)) (read-from-string (nth 1 line)) (read-from-string (nth 2 line)))
      )


      )
    )
  )
)

;; CALL MAIN FUNCTION
(main)
