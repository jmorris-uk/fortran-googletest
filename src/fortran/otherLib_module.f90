module otherLib_module

    implicit none
    
    integer, public, bind(C) :: shared_value = 15

end module otherLib_module