webpackJsonp([7],{148:function(e,t,n){"use strict";function a(e){return e&&e.__esModule?e:{"default":e}}var r=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var a in n)Object.prototype.hasOwnProperty.call(n,a)&&(e[a]=n[a])}return e};Object.defineProperty(t,"__esModule",{value:!0});var l=n(1),o=a(l),u=n(151),s=a(u),i=n(150),c=a(i);t["default"]=o["default"].createClass({displayName:"LocalSuggestField",propTypes:{data:o["default"].PropTypes.array.isRequired,onChange:o["default"].PropTypes.func},getInitialState:function(){return{suggestions:[]}},filterSuggestions:function(e){var t=new RegExp("^"+e,"i");return this.props.data.filter(function(e){return t.test(e)})},onTextChange:function(e){this.props.onChange&&this.props.onChange(e),this.setState({suggestions:e?this.filterSuggestions(e):[]})},renderSuggestion:function(e,t){var n=t.value;return(0,s["default"])(n,e)},getSuggestionValue:function(e){return e},render:function(){return o["default"].createElement(c["default"],r({},this.props,{renderSuggestion:this.renderSuggestion,getSuggestionValue:this.getSuggestionValue,suggestions:this.state.suggestions,onChange:this.onTextChange}))}})},257:function(e,t){"use strict";Object.defineProperty(t,"__esModule",{value:!0});var n="search/v0";t["default"]={MODULE_URL:n,QUERY_URL:n+"/query",RESULT_URL:n+"/result"}},447:function(e,t,n){"use strict";function a(e){return e&&e.__esModule?e:{"default":e}}Object.defineProperty(t,"__esModule",{value:!0}),t.SearchActions=void 0;var r=n(3),l=a(r),o=n(257),u=a(o),s=n(6),i=a(s),c=n(25),d=a(c),f=t.SearchActions=l["default"].createActions([{download:{asyncResult:!0}}]);f.download.listen(function(e,t){return i["default"].post(u["default"].RESULT_URL+"/"+e.itemInfo.id+"/download",t).then(f.download.completed)["catch"](function(t){return f.download.failed(e,t)})}),f.download.failed.listen(function(e,t){d["default"].error({title:e.itemInfo.name,message:"Failed to queue the item: "+t.message})}),t["default"]=f},451:function(e,t,n){"use strict";function a(e){return e&&e.__esModule?e:{"default":e}}Object.defineProperty(t,"__esModule",{value:!0});var r=n(1),l=a(r),o=n(6),u=a(o),s=n(95),i=a(s),c=n(144),d=a(c),f=n(148),h=a(f),m=n(33),p=a(m);t["default"]=l["default"].createClass({displayName:"HistoryInput",propTypes:{historyId:l["default"].PropTypes.number.isRequired},getInitialState:function(){return{history:[]}},componentDidMount:function(){this.loadHistory()},loadHistory:function(){var e=this;u["default"].get(i["default"].ITEMS_URL+"/"+this.props.historyId).then(function(t){e.setState({history:t})})["catch"](function(e){return console.error("Failed to load history: "+e)})},handleSubmit:function(e){d["default"].add(this.props.historyId,e),this.loadHistory(),this.props.submitHandler(e)},render:function(){return l["default"].createElement(h["default"],{data:this.state.history,placeholder:"Enter search string...",submitHandler:this.handleSubmit,button:l["default"].createElement(p["default"],{icon:"search icon",caption:"Search",loading:this.props.running})})}})},496:function(e,t,n){"use strict";function a(e){return e&&e.__esModule?e:{"default":e}}function r(e,t){var n={};for(var a in e)t.indexOf(a)>=0||Object.prototype.hasOwnProperty.call(e,a)&&(n[a]=e[a]);return n}Object.defineProperty(t,"__esModule",{value:!0});var l=n(1),o=a(l),u=n(447),s=a(u),i=n(588),c=a(i),d=n(52),f=n(70),h=a(f),m=n(69),p=n(49),g=a(p),y=n(30),v=n(17),w=a(v),_=function(e){var t=e.user.nicks;return e.count>1&&(t=e.count+" users ("+t+")"),t},E=function(e){var t=e.location,n=e.cellData,a=e.rowData;r(e,["location","cellData","rowData"]);return o["default"].createElement(y.TableUserMenu,{text:_(n),user:n.user,directory:a.path,location:t,userIcon:"simple",ids:["browse","message"]})},S=o["default"].createClass({displayName:"ResultTable",_rowClassNameGetter:function(e){return g["default"].dupeToStringType(e.dupe)},emptyRowsNodeGetter:function(){return this.props.running?null:this.props.searchString?o["default"].createElement(w["default"],{title:'No results found for "'+this.props.searchString+'"',description:o["default"].createElement("div",{className:"ui bulleted list"},o["default"].createElement("div",{className:"item"},"Ensure that you spelled the words correctly"),o["default"].createElement("div",{className:"item"},"Use different keywords"),o["default"].createElement("div",{className:"item"},"You are searching too frequently (hubs often have a minimum search interval)"),o["default"].createElement("div",{className:"item"},"If you never receive results for common search terms, make sure that your connectivity settings are configured properly"))}):null},render:function(){return o["default"].createElement(h["default"],{emptyRowsNodeGetter:this.emptyRowsNodeGetter,rowClassNameGetter:this._rowClassNameGetter,store:c["default"]},o["default"].createElement(d.Column,{name:"Name",width:200,columnKey:"name",flexGrow:8,cell:o["default"].createElement(m.FileDownloadCell,{location:this.props.location,handler:s["default"].download,userGetter:function(e){return e.users.user}})}),o["default"].createElement(d.Column,{name:"Size",width:60,columnKey:"size",cell:o["default"].createElement(m.SizeCell,null),flexGrow:1}),o["default"].createElement(d.Column,{name:"Type",width:80,columnKey:"type",flexGrow:1}),o["default"].createElement(d.Column,{name:"Relevancy",width:60,columnKey:"relevancy",cell:o["default"].createElement(m.DecimalCell,null),flexGrow:1}),o["default"].createElement(d.Column,{name:"Connection",width:60,columnKey:"connection",cell:o["default"].createElement(m.ConnectionCell,null),flexGrow:2}),o["default"].createElement(d.Column,{name:"Users",width:120,columnKey:"users",flexGrow:3,cell:o["default"].createElement(E,{location:this.props.location})}),o["default"].createElement(d.Column,{name:"Last modified",width:80,columnKey:"time",cell:o["default"].createElement(m.DurationCell,null),flexGrow:1}),o["default"].createElement(d.Column,{name:"Slots",width:60,columnKey:"slots",flexGrow:1}))}});t["default"]=S},497:function(e,t,n){"use strict";function a(e){return e&&e.__esModule?e:{"default":e}}Object.defineProperty(t,"__esModule",{value:!0});var r=n(1),l=a(r),o=n(6),u=a(o),s=n(95),i=n(257),c=a(i),d=n(451),f=a(d),h=n(165),m=a(h);n(810);var p=n(496),g=a(p),y=4e3,v=l["default"].createClass({displayName:"Search",_handleSearch:function(e){console.log("Searching"),clearTimeout(this._searchTimeout),u["default"].post(c["default"].QUERY_URL,{pattern:e}).then(this.onSearchPosted)["catch"](function(e){return console.error("Failed to post search: "+e)}),this.setState({searchString:e,running:!0})},onSearchPosted:function(e){var t=this;this._searchTimeout=setTimeout(function(){return t.setState({running:!1})},e.queue_time+y)},getInitialState:function(){return{searchString:null,running:!1}},render:function(){return l["default"].createElement(m["default"],{offlineMessage:"You must to be connected to at least one hub in order to perform searches"},l["default"].createElement("div",{className:"search-layout full-height"},l["default"].createElement("div",{className:"search-container"},l["default"].createElement("div",{className:"search-area"},l["default"].createElement(f["default"],{historyId:s.HistoryEnum.SEARCH,submitHandler:this._handleSearch,running:this.state.running}))),l["default"].createElement(g["default"],{searchString:this.state.searchString,running:this.state.running,location:this.props.location})))}});t["default"]=v},588:function(e,t,n){"use strict";function a(e){return e&&e.__esModule?e:{"default":e}}Object.defineProperty(t,"__esModule",{value:!0});var r=n(3),l=a(r),o=n(72),u=a(o);t["default"]=l["default"].createStore({_viewName:"search_view",_apiUrl:"search/v0",mixins:[(0,u["default"])("relevancy",!1)]})},607:function(e,t,n){t=e.exports=n(10)(),t.push([e.id,".search-container{width:100%;height:50px;margin-bottom:5px}.search-container .search-area{width:90%;max-width:600px;margin-left:auto;margin-right:auto}.search-area,.search-area .react-autosuggest__container{flex:1}.search-area,.search-area input{width:100%}.search-area button{display:inline-block!important}.search-layout{display:flex;flex-direction:column}",""])},810:[830,607]});
//# sourceMappingURL=search.chunk.js.map