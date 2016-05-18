angular.module('starter.controllers', [])


.controller('arduino', function($scope, $stateParams, $http) {
  $scope.botones=[{id:5},{id:6},{id:7},{id:8},{id:9}]
  $scope.botones_estado={5:0,6:0,7:0,8:0,9:0}
  console.log("adasd")

  $scope.click=function(id){
   console.log("led "+$scope.botones_estado[id]+" : "+"192.168.0.177/?led="+id+"&estado=1"+" _ "+JSON.stringify($scope.botones_estado))
   if($scope.botones_estado[id]==0){
      $http({method: 'GET', url:"http://192.168.0.177//?led="+id+"&estado=1"})
       $scope.botones_estado[id]=1;
   }else if($scope.botones_estado[id]==1){
      $http({method: 'GET', url:"http://192.168.0.177//?led="+id+"&estado=0"})
       $scope.botones_estado[id]=0;
   }
  }

})


