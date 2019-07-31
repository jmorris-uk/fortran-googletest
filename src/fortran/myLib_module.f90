module myLib

    use iso_c_binding

    implicit none

    public :: mySub

    integer, parameter :: dp = selected_real_kind(15, 307)

contains

    subroutine mySub(x, y) bind(C, name="myLib_mySub")

        use otherLib_module, only : shared_value

        integer, intent(in) :: x
        integer, intent(out) :: y

        y = x*shared_value
    
    end subroutine mySub

    real(kind=dp)  function binomial(n,k) result(coefficient) &
        bind (C, name="myLib_binomial")
  
        implicit none

        integer, intent(in) :: n, k
        integer :: numerator, i
  
        if (k == 0) then
            coefficient = 1
        else
            coefficient = 1.0D0
            do i = 1, k
                numerator = n + 1 -i
                coefficient = coefficient * real(numerator)/real(i)
            end do
        end if
  
    end function binomial

end module myLib